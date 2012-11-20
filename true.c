/*
	true.c : always returns 0. ALWAYS!
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void usage(const char *execname)
{
	printf("Usage: %s [options]\n"
	"  Options\n"
	"    --help: Show this help (why would you even need help\n"
	"            in the first place for a program like this?)\n"
	"    --version: Print program version\n", execname);
}

void version(void)
{
	printf("true 0.1a\n"
	"Copyright (C) UnSX Team.\n"
	"Part of Au, the Alice in Userland project.\n"
	"Released under the MIT License.\n");
}

int main(int argc, char **argv)
{
	if ( argc > 1 )
	{
		if ( strcmp(argv[1],"--help") == 0 )
			usage(argv[0]);
		else if ( strcmp(argv[1],"--version") == 0 )
			version();
	}
	return 0;
}
