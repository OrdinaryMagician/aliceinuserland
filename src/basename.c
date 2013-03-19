/*
	basename.c : print the actual filename of something without its path
	(C)2012-2013-2013 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <string.h>

int main( int argc, char **argv )
{
	if ( argc <= 1 )
		return 1;
	char *base = argv[1];
	char *memb = strtok(argv[1],"/");
	while ( memb )
	{
		base = memb;
		memb = strtok(NULL,"/");
	}
	return printf("%s\n",base)&0;
}
