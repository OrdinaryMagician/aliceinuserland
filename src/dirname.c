/*
	dirname.c : print the path of the directory something is on.
	(C)2012-2014 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>

int main( int argc, char **argv )
{
	if ( argc <= 1 ) return 1;
	char *dir = argv[1], *find = dir;
	while ( *argv[1] )
	{
		if ( *argv[1] == '/' && *(argv[1]+1) ) find = argv[1];
		argv[1]++;
	}
	if ( *find != '/' ) return puts(".")&0;
	if ( find == dir ) return puts("/")&0;
	*find = 0;
	return puts(dir)&0;
}
