/*
	logname.c : get user we logged in as.
	(C)2012-2014 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <stdio.h>
#include <unistd.h>

int main( void )
{
	char *lname;
	return (lname=getlogin())?(puts(lname)==EOF):1;
}
