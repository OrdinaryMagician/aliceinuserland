/*
	yes.c : automated y/n handler for lazy people.
	(C)2012-2014 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "helpers.h"

int main( int argc, char **argv )
{
	int i, strsiz;
	if ( argc <= 1 )
	{
		while( puts("y") >= 0 );
		return bail("yes: /dev/stdout: %s\n",strerror(errno))&0;
	}
	strsiz = 0;
	i = 1;
	while( i < argc ) strsiz += strlen(argv[i++])+1;
	char *joinstr = malloc(strsiz);
	if ( !joinstr ) return bail("yes: %s\n",strerror(errno));
	strcpy(joinstr,"");
	i = 1;
	while ( i < argc )
	{
		strcat(joinstr,argv[i++]);
		strcat(joinstr,&" "[i>=argc]);
	}
	while( puts(joinstr) >= 0 );
	return bail("yes: /dev/stdout: %s\n",strerror(errno))&0;
}
