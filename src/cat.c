/*
	cat.c : Concatenate files.
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int spew( const char *fname )
{
	int ch = 0;
	if ( strcmp(fname,"-") == 0 )
	{
		while ((ch = getchar()) != EOF)
			putchar(ch);
		return 0;
	}
	FILE *fil;
	if ( (fil = fopen(fname,"rb")) == NULL )
	{
		fprintf(stderr,"cat: %s: %s\n",fname,strerror(errno));
		return 1;
	}
	while ((ch = fgetc(fil)) != EOF)
		putchar(ch);
	fclose(fil);
	return 0;
}

int main( int argc, char **argv )
{
	int ch = 0;
	if ( argc <= 1 )
	{
		while ((ch = getchar()) != EOF)
			putchar(ch);
		return 0;
	}
	int i = 0;
	for ( i=1;i<argc;i++ )
		if ( !((i==1) && (strcmp(argv[i],"-u") == 0)) )
			if ( spew(argv[i]) )
				return 1;
	return 0;
}
