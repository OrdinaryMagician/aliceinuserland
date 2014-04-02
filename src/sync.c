/*
	sync.c : flush filesystem buffers.
	(C)2012-2014 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#define _BSD_SOURCE	// this time just for sync()
#include <unistd.h>

int main( void )
{
	sync();
	return 0;
}
