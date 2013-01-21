/*
	yes.c : automated y/n handler for lazy people.
	(C)2012-2013 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main( int argc, char **argv )
{
	int i;
	int strsiz;
	if ( argc <= 1 )
	{
		while( puts("y") > 0 );
		fprintf(stderr,"yes: stdout: %s\n",strerror(errno));
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
	while( puts(joinstr) > 0 );
	fprintf(stderr,"yes: stdout: %s\n",strerror(errno));
	return 0;
}
