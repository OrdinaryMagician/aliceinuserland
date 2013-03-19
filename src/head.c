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
#include <helpers.h>

int head( unsigned int nl, char *fname )
{
	FILE *tf; 
	if ( (tf = fopen(fname,"r")) == NULL )
		return bail("head: %s: %s\n",fname,strerror(errno));
	int ch;
	do
	{
		ch = fgetc(tf);
		if ( ch == EOF )
			break;
		if ( ferror(tf) )
		{
			fclose(tf);
			return bail("head: %s: %s\n",fname,strerror(errno));
		}
		if ( ch == '\n' )
			nl--;
		if ( putchar(ch) == EOF )
		{
			fclose(tf);
			return bail("head: %s: %s\n",fname,strerror(errno));
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
