/*
	basename.c : print the actual filename of something without its path
	(C)2012-2013 Marisa Kirisame, UnSX Team.
	(C)2013 Cyphar
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	if(argc <= 1) return 1;

	char *base = strrchr(argv[1], '/') + 1;
	printf("%s\n", base);
	
	return 0;
}
