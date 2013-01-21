/*
	dirname.c : print the path of the directory something is on
	(C)2012-2013-2013 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>

int main( int argc, char **argv )
{
	if ( argc <= 1 )
		return 1;
	char *dir = argv[1];
	char *find = dir;
	while ( *argv[1] )
	{
		if ( *argv[1] == '/' && *(argv[1]+1) )
			find = argv[1];
		argv[1]++;
	}
	if ( *find != '/' )
	{
		printf(".\n");
		return 0;
	}
	if ( find == dir )
	{
		printf("/\n");
		return 0;
	}
	*find = 0;
	printf("%s\n",dir);
	return 0;
}
