/*
	yes.c : automated y/n handler for lazy people.
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>

int main (int argc, char **argv)
{
	int i;
	if ( argc > 1 )
	{
		while(1)
		{
			for(i=1;i<argc;i++)
			{
				fputs(argv[i],stdout);
				(i < (argc-1)) ? putchar(' ') : putchar('\n');
			}
		}
		return 0;
	}
	while(1)
		fputs("y\n",stdout);
	return 0;
}
