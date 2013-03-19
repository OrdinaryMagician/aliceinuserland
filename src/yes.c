/*
	yes.c : automated y/n handler for lazy people.
	(C)2012-2013 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <helpers.h>

int main( int argc, char **argv )
{
	int i;
	int strsiz;
	if ( argc <= 1 )
	{
		while( puts("y") > 0 );
		return bail("yes: /dev/stdout: %s\n",strerror(errno))&0;
	}
	strsiz = 0;
	i = 0;
	while( i < argc )
		strsiz += strlen(argv[i++]+1);
	char joinstr[strsiz];
	strcpy(joinstr,"");
	i = 0;
	while ( i < argc )
	{
		strcat(joinstr,argv[i++]);
		if ( i < argc )
			strcat(joinstr," ");
	}
	while( puts(joinstr) > 0 );
		return bail("yes: /dev/stdout: %s\n",strerror(errno))&0;
}
