/*
	echo.c : Standalone version of echo from Bash.
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"

#define OPT_ESC 1
#define OPT_NONL 2

void usage(const char *execname)
{
	printf("Usage: %s [options] [string]\n"
	"  Options\n"
	"    -e: Interpret backslash escapes (see echo section in Bash manpage for list)\n"
	"    -E: DO NOT interpret backslash escapes (deprecated)\n"
	"    -n: Don't terminate string with a newline\n"
	"    --help: Show this help\n"
	"    --version: Print program version\n"
	"  String\n"
	"    First sequence to not be recognized as an option indicates\n"
	"    the beginning of all the text to output\n", execname);
}

void version(void)
{
	printf("echo 0.1a\n"
	"Copyright (C) UnSX Team.\n"
	"Part of Au, the Alice in Userland project.\n"
	"Released under the MIT License.\n");
}

int main (int argc, char **argv)
{
	unsigned char options = 0;
	int i = 0, j = 0, k = 0, nc = 0;
	unsigned long int unic = 0;
	char *transl = NULL;
	char *funic = NULL;
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
					if ( strcmp(argv[i],"--help") == 0 )
					{
						usage(argv[0]);
						return 0;
					}
					else if ( strcmp(argv[i],"--version") == 0 )
					{
						version();
						return 0;
					}
					else
						break;
				}
				else if ( isin(argv[i][1],"eEn") )
				{
					bool bNoInc = false;
					j = 1;
					do
					{
						switch ( argv[i][j] )
						{
							case 'e':
								options = options|OPT_ESC;
								break;
							case 'E':
								options = options&(~OPT_ESC);
								break;
							case 'n':
								options = options|OPT_NONL;
								break;
							default:
								bNoInc = true;
								break;
						}
						j++;
					}
					while ( argv[i][j] != '\0' );
					if ( !bNoInc )
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
				transl = (char *)malloc(j+2);
				j = 0;
				do
				{
					if ( argv[i][j] == '\\' )
					{
						j++;
						switch ( argv[i][j] )
						{
							case 'a':
								transl[k] = '\007';
								j++;
								k++;
								break;
							case 'b':
								transl[k] = '\010';
								j++;
								k++;
								break;
							case 'c':
								transl[k] = '\0';
								k++;
								bSkip = true;
								break;
							case 'e':
							case 'E':
								transl[k] = '\033';
								j++;
								k++;
								break;
							case 'f':
								transl[k] = '\014';
								j++;
								k++;
								break;
							case 'n':
								transl[k] = '\012';
								j++;
								k++;
								break;
							case 'r':
								transl[k] = '\015';
								j++;
								k++;
								break;
							case 't':
								transl[k] = '\011';
								j++;
								k++;
								break;
							case 'v':
								transl[k] = '\013';
								j++;
								k++;
								break;
							case '\\':
								transl[k] = '\\';
								j++;
								k++;
								break;
							case '0':
								j++;
								nc = 3;
								transl[k] = 0;
								while( isin(argv[i][j],"01234567") && (nc > 0) )
								{
									transl[k] = transl[k]*8 + ctoh(argv[i][j]);
									nc--;
									j++;
								}
								k++;
								break;
							case 'x':
								j++;
								nc = 2;
								transl[k] = 0;
								while( isin(argv[i][j],"0123456789abcdefABCDEF") && (nc > 0) )
								{
									transl[k] = transl[k]*16 + ctoh(argv[i][j]);
									nc--;
									j++;
								}
								k++;
								break;
							case 'u':
								j++;
								nc = 4;
								transl[k] = 0;
								unic = 0;
								while( isin(argv[i][j],"0123456789abcdefABCDEF") && (nc > 0) )
								{
									unic = unic*16 + ctoh(argv[i][j]);
									nc--;
									j++;
								}
								funic = toutf8(unic);
								nc = 0;
								do
								{
									transl[k] = funic[nc];
									k++;
									nc++;
								}
								while ( funic[nc] != '\0' );
								break;
							case 'U':
								j++;
								nc = 8;
								transl[k] = 0;
								unic = 0;
								while( isin(argv[i][j],"0123456789abcdefABCDEF") && (nc > 0) )
								{
									unic = unic*16 + ctoh(argv[i][j]);
									nc--;
									j++;
								}
								funic = toutf8(unic);
								nc = 0;
								do
								{
									transl[k] = funic[nc];
									k++;
									nc++;
								}
								while ( funic[nc] != '\0' );
								break;
							default:
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
				while ( (argv[i][j] != '\0') && !bSkip );
				if ( (i+1) == argc )
				{
					if ( !(options&OPT_NONL) )
					{
						transl[k] = '\n';
						k++;
					}
				}
				else
				{
					transl[k] = ' ';
					k++;
				}
				transl[k] = '\0';
				nprints(transl,k);
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
