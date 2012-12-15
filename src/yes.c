/*
	yes.c : automated y/n handler for lazy people.
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <string.h>

int main( int argc, char **argv )
{
	int i;
	int strsiz;
	if ( argc <= 1 )
	{
		for(;;)
			puts("y");
		return 0;
	}
	strsiz = 0;
	for( i=1; i<argc; i++ )
		strsiz += strlen(argv[i]+1);
	char joinstr[strsiz];
	strcpy(joinstr,"");
	for( i=1; i<argc; i++ )
	{
		strcat(joinstr,argv[i]);
		if ( i < (argc-1) )
			strcat(joinstr," ");
	}
	for(;;)
		puts(joinstr);
	return 0;
}
