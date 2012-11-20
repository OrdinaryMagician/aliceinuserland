/*
	echo.c : Standalone version of echo from Bash.
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OPT_ESC 1
#define OPT_NONL 2

void usage(const char *execname)
{
	printf("Usage: %s [options] [string]\n", execname);
	printf("  Options\n");
	printf("    -e: Interpret backslash escapes (see echo section in Bash manpage for list)\n");
	printf("    -E: DO NOT interpret backslash escapes (deprecated)\n");
	printf("    -n: Don't terminate string with a newline\n");
	printf("    --help: Show this help\n");
	printf("    --version: Print program version\n");
	printf("  String\n");
	printf("    First sequence to not be recognized as an option indicates\n");
	printf("    the beginning of all the text to output\n");
}

void version()
{
	printf("echo 0.1a\n");
	printf("Copyright (C) UnSX Team.\n");
	printf("Part of Au, the Alice in Userland project.\n");
	printf("Released under the MIT License.\n");
}

bool isin(const char c, const char *set)
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

bool eqstr(const char *a, const char *b)
{
	int i = 0;
	do
	{
		if ( a[i] != b[i] )
			return false;
		i++;
	}
	while ( (a[i] != '\0') && (b[i] != '\0') );
	return true;
}

const char* toutf8(unsigned long int unichar)
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

int main (int argc, char **argv)
{
	unsigned char options = 0;
	int i = 0, j = 0, k = 0;
	char *transl = NULL;
	bool bSkip = false;
	if ( argc > 1 )
	{
		i = 1;
		while ( i < argc )
		{
			if ( argv[i][0] == '-' )
			{
				if ( argv[i][1] == '-') 
				{
					if ( eqstr(argv[i],"--help") )
					{
						usage(argv[0]);
						return 0;
					}
					else if ( eqstr(argv[i],"--version") )
					{
						version();
						return 0;
					}
					else
						break;
				}
				else if ( isin(argv[i][1],"eEn") )
				{
					j = 1;
					do
					{
						if ( argv[i][j] == 'e' )
							options = options|OPT_ESC;
						else if ( argv[i][j] == 'E' )
							options = options&(~OPT_ESC);
						else if ( argv[i][j] == 'n' )
							options = options|OPT_NONL;
						else
							break;
						j++;
					}
					while ( isin(argv[i][j],"eEn") );
					i++;
					break;
				}
				else
					break;
			}
			else
				break;
			i++;
		}
		while ( (i < argc) && !bSkip )
		{
			if ( options&OPT_ESC )
			{
				j = 0;
				k = 0;
				do
					j++;
				while ( argv[i][j] != '\0' );
				transl = (char *)malloc(j+1);
				j = 0;
				do
				{
					if ( argv[i][j] == '\\' )
					{
						if ( argv[i][j+1] == 'a' )
						{
							transl[k] = '\007';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'b' )
						{
							transl[k] = '\010';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'c' )
						{
							transl[k] = '\0';
							j++;
							k++;
							bSkip = true;
							break;
						}
						else if ( (argv[i][j+1] == 'e') || (argv[i][j+1] == 'E') )
						{
							transl[k] = '\033';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'f' )
						{
							transl[k] = '\014';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'n' )
						{
							transl[k] = '\012';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'r' )
						{
							transl[k] = '\015';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 't' )
						{
							transl[k] = '\011';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'v' )
						{
							transl[k] = '\013';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == '\\' )
						{
							transl[k] = '\\';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == '0' )
						{
							transl[k] = '\007';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'x' )
						{
							transl[k] = '\007';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'u' )
						{
							transl[k] = '\007';
							j+=2;
							k++;
						}
						else if ( argv[i][j+1] == 'U' )
						{
							transl[k] = '\007';
							j+=2;
							k++;
						}
						else
						{
							transl[k] = argv[i][j];
							j++;
							k++;
						}
					}
					else
					{
						transl[k] = argv[i][j];
						j++;
						k++;
					}
				}
				while ( argv[i][j] != '\0' );
				transl[k] = '\0';
				(i+1) == argc ? (options&OPT_NONL ? printf("%s",transl) : printf("%s\n",transl)) : printf("%s ",transl);
				free(transl);
			}
			else
				(i+1) == argc ? (options&OPT_NONL ? printf("%s",argv[i]) : printf("%s\n",argv[i])) : printf("%s ",argv[i]);
			i++;
		}
		return 0;
	}
	printf("\n");
	return 0;
}
