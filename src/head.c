/*
	head.c : Print first n lines of a text.
	(C)2012-2013 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int head( unsigned int nl, char *fname )
{
	FILE *tf; 
	if ( (tf = fopen(fname,"r")) == NULL )
	{
		fprintf(stderr,"head: %s: %s\n",fname,strerror(errno));
		return 1;
	}
	int ch;
	do
	{
		ch = fgetc(tf);
		if ( ferror(tf) )
		{
			fprintf(stderr,"head: %s: %s\n",fname,strerror(errno));
			fclose(tf);
			return 1;
		}
		if ( ch == '\n' )
			nl--;
		if ( putchar(ch) == EOF )
		{
			fprintf(stderr,"head: stdout: %s\n",strerror(errno));
			fclose(tf);
			return 0;
		}
	}
	while ( (ch != EOF) && (nl > 0) );
	fclose(tf);
	return 0;
}

int main( int argc, char **argv )
{
	int skip = 1;
	unsigned int nl = 10;
	if ( (argc > 2) && !strcmp(argv[1],"-n") )
	{
		nl = atoi(argv[2]);
		skip += 2;
	}
	return head(nl,(argc>skip)?argv[skip]:"/dev/stdin");
}
