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

bool direct = false;

int dspew( const char *fname )
{
	int filedes = 0;
	int retrn = 0;
	char ch = 0;
	if ( strcmp(fname,"-") == 0 )
	{
		do
		{
			retrn = read(STDIN_FILENO,&ch,1);
			if ( retrn > 0 )
				write(STDOUT_FILENO,&ch,1);
			if ( retrn == -1 )
			{
				fprintf(stderr,"cat: stdin: %s\n",strerror(errno));
				return 1;
			}
		}
		while ( retrn > 0 );
		return 0;
	}
	if ( (filedes = open(fname,O_RDONLY)) == -1 )
	{
		fprintf(stderr,"cat: %s: %s\n",fname,strerror(errno));
		return 1;
	}
	do
	{
		retrn = read(filedes,&ch,1);
		if ( retrn > 0 )
			write(STDOUT_FILENO,&ch,1);
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
		return spew("-");
	int i = 0;
	for ( i=1;i<argc;i++ )
	{
		if ( (i==1) && (strcmp(argv[i],"-u") == 0) )
		{
			direct = true;
			if ( argc == 2 )
				return dspew("-");
			continue;
		}
		if ( direct ? dspew(argv[i]) : spew(argv[i]) )
				return 1;
	}
	return 0;
}
