/*
	echo.c : Standalone version of echo from Bash.
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <helpers.h>
#define OPT_ESC 1
#define OPT_NONL 2

unsigned char options = 0;

/*
   get options, return whether or not this argument should be
   skipped when printing (i.e.: if it's not recognized as an option)
*/
bool getopts( const char *arg )
{
	int i = 0;
	bool skipme = true;
	while ( arg[i] != 0 )
	{
		switch ( arg[i] )
		{
		case 'e':
			options = options|OPT_ESC;
			break;
		case 'n':
			options = options|OPT_NONL;
			break;
		default:
			skipme = false;
			break;
		}
		i++;
	}
	return skipme;
}

int main( int argc, char **argv )
{
	int i = 0, j = 0, sch = 0;
	i = 1;
	while ( i < argc )
	{
		if ( (argv[i][0] == '-') && isin(argv[i][1],"en") && getopts(argv[i]+1) )
			i++;
		break;
	}
	bool skip = false;
	while ( i < argc )
	{
		if ( !(options&OPT_ESC) )
		{
			fputs(argv[i],stdout);
			( (i+1) == argc ) ? ( (options&OPT_NONL) ? putchar('\0') : putchar('\n')) : putchar(' ');
			i++;
			continue;
		}
		j = 0;
		skip = false;
		while ( !skip )
		{
			sch = descape(argv[i]+j);
			j += sch;
			if ( sch == -1 )
				return 0;
			if ( sch == 0 )
				skip = true;
		}
		if ( i < (argc-1) )
			putchar(' ');
		else
			putchar('\n');
		i++;
	}
	return 0;
}
