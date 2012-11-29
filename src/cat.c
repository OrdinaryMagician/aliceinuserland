/*
	cat.c : Concatenate files.
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BLOCKSIZE
#define BLOCKSIZE 131072
#endif

bool noblock = false;

int stdinspew( int blocksize )
{
	int retrn = 0;
	char block[blocksize];
	do
	{
		retrn = read(STDIN_FILENO,block,blocksize);
		if ( retrn > 0 )
			write(STDOUT_FILENO,block,retrn);
		if ( retrn == -1 )
		{
			fprintf(stderr,"cat: stdin: %s\n",strerror(errno));
			return 1;
		}
	}
	while ( retrn > 0 );
	return 0;
}

int spew( const char *fname, int blocksize )
{
	if ( strcmp(fname,"-") == 0 )
		return stdinspew(blocksize);

	int filedes = 0;
	int retrn = 0;
	char block[blocksize];
	if ( (filedes = open(fname,O_RDONLY)) == -1 )
	{
		fprintf(stderr,"cat: %s: %s\n",fname,strerror(errno));
		return 1;
	}
	do
	{
		retrn = read(filedes,block,blocksize);
		if ( retrn > 0 )
			write(STDOUT_FILENO,block,retrn);
		if ( retrn == -1 )
		{
			fprintf(stderr,"cat: %s: %s\n",fname,strerror(errno));
			return 1;
		}
	}
	while ( retrn > 0 );
	close(filedes);
	return 0;
}

int main( int argc, char **argv )
{
	int blksize = 0;
	char *gotblk = getenv("AUIO_BLKSIZE");
	blksize = ( (gotblk != NULL) && (atoi(gotblk) > 0) ) ? atoi(gotblk) : BLOCKSIZE;
	if ( argc <= 1 )
		return spew("-",blksize);
	int i = 0;
	for ( i=1; i<argc; i++ )
	{
		if ( (i==1) && (strcmp(argv[i],"-u") == 0) )
		{
			noblock = true;
			if ( argc == 2 )
				return spew("-",1);
			continue;
		}
		if ( spew(argv[i],( noblock ? 1 : blksize )) )
			return 1;
	}
	return 0;
}
