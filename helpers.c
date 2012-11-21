/*
	helpers.c : some few helper functions
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

extern bool isin(const char c, const char *set)
{
	int i = 0;
	do
	{
		if ( c == set[i] )
			return true;
		i++;
	}
	while ( set[i] != '\0' );
	return false;
}

extern void nprints(const char *s, const int len)
{
	int i;
	for ( i = 0; i<len; i++ )
		putchar(s[i]);
}

extern int ctoh(const unsigned char c)
{
	if ( c >= '0' && c <= '9' )
		return c - '0';
	else if ( c >= 'a' && c <= 'f' )
		return (c  - 'a') + 10;
	else if ( c >= 'A' && c <= 'F' )
		return (c  - 'A') + 10;
	else
		return 0;
}

extern void pututf8(unsigned long int unichar)
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

extern char* toutf8(unsigned long int unichar)
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
