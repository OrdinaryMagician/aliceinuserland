/*
	cat.c : Concatenate files.
	(C)2012-2014 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include "helpers.h"

#ifndef BLOCKSIZE
#define BLOCKSIZE 131072
#endif

int cat( const char *fname)
{
	int filedes = 0, retrn = 0;
	char block[BLOCKSIZE];
	if ( (filedes = open(fname,O_RDONLY)) == -1 )
		return bail("cat: %s: %s\n",fname,strerror(errno));
	do
	{
		retrn = read(filedes,block,BLOCKSIZE);
		if ( retrn == -1 )
		{
			close(filedes);
			return bail("cat: %s: %s\n",fname,strerror(errno));
		}
		if ( !retrn ) continue;
		retrn = write(STDOUT_FILENO,block,retrn);
		if ( retrn == -1 )
		{
			close(filedes);
			return bail("cat: %s: %s\n",fname,strerror(errno));
		}
	}
	while ( retrn > 0 );
	close(filedes);
	return 0;
}

int main( int argc, char **argv )
{
	if ( argc <= 1 ) return cat("/dev/stdin");
	int i = 1;
	while ( i < argc ) if ( cat(argv[i++]) ) return 1;
	return 0;
}
