/*
	true.c : always returns 0. ALWAYS!
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdbool.h>

void usage(const char *execname)
{
	printf("Usage: %s [options]\n"
	"  Options\n"
	"    --help: Show this help (why would you even need help\n"
	"            in the first place for a program like this?)\n"
	"    --version: Print program version\n", execname);
}

void version()
{
	printf("true 0.1a\n"
	"Copyright (C) UnSX Team.\n"
	"Part of Au, the Alice in Userland project.\n"
	"Released under the MIT License.\n");
}

bool eqstr(const char *a, const char *b)
{
	int i = 0;
	do
	{
		if ( a[i] != b[i] )
			return false;
		i++;
	}
	while ( (a[i] != '\0') && (b[i] != '\0') );
	return true;
}

int main(int argc, char **argv)
{
	if ( argc > 1 )
	{
		if ( eqstr(argv[1],"--help") )
			usage(argv[0]);
		else if ( eqstr(argv[1],"--version") )
			version();
	}
	return 0;
}
