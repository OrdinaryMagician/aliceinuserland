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
int main (int argc, char **argv)
{
	unsigned char options = 0;
	int i = 0, j = 0, nc = 0;
	if ( argc > 1 )
	{
		i = 1;
		while ( i < argc )
		{
			if ( argv[i][0] == '-' )
			{
				if ( isin(argv[i][1],"eEn") )
				{
					bool noincr = false;
					j = 1;
					while ( argv[i][j] != 0 )
					{
						switch (argv[i][j] )
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
								noincr = true;
								break;
						}
						j++;
					}
					if ( !noincr )
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
		bool skip = false;
		while ( (i < argc) && !skip )
		{
			if ( options&OPT_ESC )
			{
				j = 0;
				unsigned char trch = 0;
				unsigned long int unich = 0;
				while ( (argv[i][j] != 0) && !skip )
				{
					if ( argv[i][j] == '\\' )
					{
						j++;
						switch ( argv[i][j] )
						{
							case 'a':
								putchar('\007');
								j++;
								break;
							case 'b':
								putchar('\010');
								j++;
								break;
							case 'c':
								putchar('\0');
								skip = true;
								break;
							case 'e':
							case 'E':
								putchar('\033');
								j++;
								break;
							case 'f':
								putchar('\014');
								j++;
								break;
							case 'n':
								putchar('\012');
								j++;
								break;
							case 'r':
								putchar('\015');
								j++;
								break;
							case 't':
								putchar('\011');
								j++;
								break;
							case 'v':
								putchar('\013');
								j++;
								break;
							case '\\':
								putchar('\\');
								j++;
								break;
							case '0':
								j++;
								nc = 3;
								trch = 0;
								while( isin(argv[i][j],"01234567") && (nc > 0) )
								{
									trch = trch*8 + ctoh(argv[i][j]);
									nc--;
									j++;
								}
								putchar(trch);
								break;
							case 'x':
								j++;
								nc = 2;
								trch = 0;
								while( isin(argv[i][j],"0123456789abcdefABCDEF") && (nc > 0) )
								{
									trch = trch*16 + ctoh(argv[i][j]);
									nc--;
									j++;
								}
								putchar(trch);
								break;
							case 'u':
								j++;
								nc = 4;
								unich = 0;
								while( isin(argv[i][j],"0123456789abcdefABCDEF") && (nc > 0) )
								{
									unich = unich*16 + ctoh(argv[i][j]);
									nc--;
									j++;
								}
								pututf8(unich);
								break;
							case 'U':
								j++;
								nc = 8;
								unich = 0;
								while( isin(argv[i][j],"0123456789abcdefABCDEF") && (nc > 0) )
								{
									unich = unich*16 + ctoh(argv[i][j]);
									nc--;
									j++;
								}
								pututf8(unich);
							default:
								putchar(argv[i][j]);
								j++;
						}
					}
					else
					{
						putchar(argv[i][j]);
						j++;
					}
				}
				while ( (argv[i][j] != '\0') && !skip );
				if ( i < (argc-1) )
					putchar(' ');
				else
					putchar('\n');
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
