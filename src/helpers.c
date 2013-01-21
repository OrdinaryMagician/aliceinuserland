/*
	helpers.c : some "few" helper functions
	(C)2012-2013 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
   check if a character is inside the specified set
*/
bool isin( const char c, const char *set )
{
	int i = 0;
	while ( set[i] != '\0' )
	{
		if ( c == set[i] )
			return true;
		i++;
	}
	return false;
}

/*
   something like write(1,s,len) but with stdio functions
*/
void nprints( const char *s, const int len )
{
	int i;
	for ( i=0; i<len; i++ )
		putchar(s[i]);
}

/*
   try to interpret a character as an hexadecimal digit
*/
int ctoh( const unsigned char c )
{
	return ((c>='0')&&(c<='9'))?(c-'0'):((c>='a')&&(c<='f'))?((c-'a')+10):((c>='A')&&(c<='F'))?((c-'A')+10):0;
}

/*
   print the UTF-8 char sequence corresponding to a specific unicode value
*/
void pututf8( unsigned long int unichar )
{
	if ( unichar <= 0x7f )
		putchar(unichar%0x80);
	else if ( unichar <= 0x7ff )
	{
		putchar(0xC0 + (unichar>>6)%0x20);
		putchar(0x80 + unichar%0x40);
	}
	else if ( unichar <= 0xffff )
	{
		putchar(0xE0 + (unichar>>12)%0x10);
		putchar(0x80 + (unichar>>6)%0x40);
		putchar(0x80 + unichar%0x40);
	}
	else if ( unichar <= 0x1fffff )
	{
		putchar(0xF0 + (unichar>>18)%0x08);
		putchar(0x80 + (unichar>>12)%0x40);
		putchar(0x80 + (unichar>>6)%0x40);
		putchar(0x80 + unichar%0x40);
	}
	else if ( unichar <= 0x3ffffff )
	{
		putchar(0xF8 + (unichar>>24)%0x04);
		putchar(0x80 + (unichar>>18)%0x40);
		putchar(0x80 + (unichar>>12)%0x40);
		putchar(0x80 + (unichar>>6)%0x40);
		putchar(0x80 + unichar%0x40);
	}
	else if ( unichar <= 0x7fffffff )
	{
		putchar(0xFC + (unichar>>30)%0x02);
		putchar(0x80 + (unichar>>24)%0x40);
		putchar(0x80 + (unichar>>18)%0x40);
		putchar(0x80 + (unichar>>12)%0x40);
		putchar(0x80 + (unichar>>6)%0x40);
		putchar(0x80 + unichar%0x40);
	}
}

/*
   create a string from an unicode character value and return a pointer to it
*/
char* toutf8( unsigned long int unichar )
{
	char *retstr = NULL;
	if ( unichar <= 0x7f )
	{
		retstr = (char *)malloc(2);
		retstr[0] = unichar%0x80;
		retstr[1] = '\0';
	}
	else if ( unichar <= 0x7ff )
	{
		retstr = (char *)malloc(3);
		retstr[0] = 0xC0 + (unichar>>6)%0x20;
		retstr[1] = 0x80 + unichar%0x40;
		retstr[2] = '\0';
	}
	else if ( unichar <= 0xffff )
	{
		retstr = (char *)malloc(4);
		retstr[0] = 0xE0 + (unichar>>12)%0x10;
		retstr[1] = 0x80 + (unichar>>6)%0x40;
		retstr[2] = 0x80 + unichar%0x40;
		retstr[3] = '\0';
	}
	else if ( unichar <= 0x1fffff )
	{
		retstr = (char *)malloc(5);
		retstr[0] = 0xF0 + (unichar>>18)%0x8;
		retstr[1] = 0x80 + (unichar>>12)%0x40;
		retstr[2] = 0x80 + (unichar>>6)%0x40;
		retstr[3] = 0x80 + unichar%0x40;
		retstr[4] = '\0';
	}
	else if ( unichar <= 0x3ffffff )
	{
		retstr = (char *)malloc(6);
		retstr[0] = 0xF8 + (unichar>>24)%0x4;
		retstr[1] = 0x80 + (unichar>>18)%0x40;
		retstr[2] = 0x80 + (unichar>>12)%0x40;
		retstr[3] = 0x80 + (unichar>>6)%0x40;
		retstr[4] = 0x80 + unichar%0x40;
		retstr[5] = '\0';
	}
	else if ( unichar <= 0x7fffffff )
	{
		retstr = (char *)malloc(7);
		retstr[0] = 0xFC + (unichar>>30)%0x2;
		retstr[1] = 0x80 + (unichar>>24)%0x40;
		retstr[2] = 0x80 + (unichar>>18)%0x40;
		retstr[3] = 0x80 + (unichar>>12)%0x40;
		retstr[4] = 0x80 + (unichar>>6)%0x40;
		retstr[5] = 0x80 + unichar%0x40;
		retstr[6] = '\0';
	}
	return retstr;
}


/*
   decode backslash escapes at beginning of string. returns number of
   characters that should be skipped in input.
   special cases: return -1 if a "\c" was found or 0 if it's a null character
*/
int descape( const char *str )
{
	int i = 0, nc = 0;
	unsigned char trch = 0;
	unsigned long int unich = 0;

	if ( str[0] != '\\' )
	{
		if ( str[0] == 0 )
			return 0;
		putchar(str[0]);
		return 1;
	}
	i++;
	switch ( str[i] )
	{
	case 'a':
		putchar('\007');
		return 2;
	case 'b':
		putchar('\010');
		return 2;
	case 'c':
		return -1;
	case 'e':
	case 'E':
		putchar('\033');
		return 2;
	case 'f':
		putchar('\014');
		return 2;
	case 'n':
		putchar('\012');
		return 2;
	case 'r':
		putchar('\015');
		return 2;
	case 't':
		putchar('\011');
		return 2;
	case 'v':
		putchar('\013');
		return 2;
	case '\\':
		putchar('\\');
		return 2;
	case '0':
		i++;
		nc = 3;
		trch = 0;
		while( isin(str[i],"01234567") && (nc > 0) )
		{
			trch = trch*8 + ctoh(str[i]);
			nc--;
			i++;
		}
		putchar(trch);
		return i;
	case 'x':
		i++;
		nc = 2;
		trch = 0;
		while( isin(str[i],"0123456789abcdefABCDEF") && (nc > 0) )
		{
			trch = trch*16 + ctoh(str[i]);
			nc--;
			i++;
		}
		putchar(trch);
		return i;
	case 'u':
		i++;
		nc = 4;
		unich = 0;
		while( isin(str[i],"0123456789abcdefABCDEF") && (nc > 0) )
		{
			unich = unich*16 + ctoh(str[i]);
			nc--;
			i++;
		}
		pututf8(unich);
		return i;
	case 'U':
		i++;
		nc = 8;
		unich = 0;
		while( isin(str[i],"0123456789abcdefABCDEF") && (nc > 0) )
		{
			unich = unich*16 + ctoh(str[i]);
			nc--;
			i++;
		}
		pututf8(unich);
		return i;
	default:
		putchar('\\');
		putchar(str[i]);
		return 2;
	}
}

