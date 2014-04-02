/*
	basename.c : print the actual filename of something without its path.
	(C)2012-2014 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <string.h>
#include <stdio.h>
int main( int argc, char **argv )
{
	if ( argc <= 1 ) return 1;
	char *base = strrchr(argv[1],'/');
	while ( base && !base[1] && (base != argv[1]) && (*base == '/') && !(*(base--)=0) );
	base = strrchr(argv[1],'/');
	return puts(((base == argv[1]) && !base[1])?base:base?(base+1):argv[1])&0;
}
