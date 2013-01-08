/*
	printenv.c : print all environment variables.
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>

int main( int argc, char **argv )
{
	for ( argv += argc+1; *argv; argv++ )
		printf("%s\n",*argv);
	return 0;
}
