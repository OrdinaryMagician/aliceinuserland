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
#include <unistd.h>
#include "helpers.h"

#ifndef BLOCKSIZE
#define BLOCKSIZE 131072
#endif

int main( int argc, char **argv )
{
	int i;
	char block[BLOCKSIZE];
	if ( argc <= 1 )
	{
		for ( i=0; i<BLOCKSIZE; i+=2 ) strncpy(block+i,"y\n",2);
		while ( write(STDOUT_FILENO,block,BLOCKSIZE) >= 0 );
		return bail("yes: /dev/stdout: %s\n",strerror(errno))&0;
	}
	int strsiz = 0;
	for ( i=1; i<argc; strsiz += strlen(argv[i++])+2 );
	char *joinstr = malloc(strsiz--);
	if ( !joinstr ) return bail("yes: %s\n",strerror(errno));
	for ( strcpy(joinstr,""), i=1; i<argc; )
	{
		strcat(joinstr,argv[i++]);
		strcat(joinstr,&" "[i>=argc]);
	}
	strcat(joinstr,"\n");
	for ( i=0; i<BLOCKSIZE; i+=strsiz ) strncpy(block+i,joinstr,strsiz);
	if ( i>BLOCKSIZE ) i-= strsiz-1;
	while( write(STDOUT_FILENO,block,i) >= 0 );
	return bail("yes: /dev/stdout: %s\n",strerror(errno))&0;
}
