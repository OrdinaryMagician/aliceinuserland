/*
	echo.c : Standalone version of echo from Bash.
	(C)2012-2013 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "helpers.h"
#define O_ESC 1
#define O_NONL 2

unsigned char opt = 0;
bool stopargs = false;

/*
   get options, return whether or not this argument should be
   skipped when printing (i.e.: if it's not recognized as an option)
*/
bool getopt( const char *arg )
{
	int i = 0;
	bool skipme = true;
	while ( arg[i] != 0 )
	{
		switch ( arg[i] )
		{
		case 'e':
			opt = opt|O_ESC;
			break;
		case 'n':
			opt = opt|O_NONL;
			break;
		case '-':
			stopargs = true;
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
		if ( (argv[i][0] == '-') && isin(argv[i][1],"en-")
			&& getopt(argv[i]+1) )
			i++;
		if ( stopargs )
			break;
	}
	bool skip = false;
	while ( i < argc )
	{
		if ( !(opt&O_ESC) )
		{
			fputs(argv[i],stdout);
			putchar(((i+1)==argc)?((opt&O_NONL)?'\0':'\n'):' ');
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
		putchar((i<(argc-1))?' ':'\n');
		i++;
	}
	return 0;
}
