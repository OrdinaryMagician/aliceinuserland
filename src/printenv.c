/*
	printenv.c : print all environment variables.
	(C)2012-2014 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>

int main( int argc, char **argv )
{
	argv += argc+1;
	while ( *argv && puts(*(argv++)) >= 0 );
	return 0;
}
