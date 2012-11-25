/*
	sleep.c : wait for some time
	(C)2012 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv)
{
	long sleeptime = 0;
	if ( argc > 1 )
		sleeptime = atol(argv[1]);
	while ( sleeptime-- > 0 )
		sleep(1);
	return 0;
}
