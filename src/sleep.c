/*
	sleep.c : wait for some time
	(C)2012-2013 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/

#define _BSD_SOURCE	// won't build with musl unless I set this

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void endwait()
{
	signal(SIGALRM,endwait);
	exit(0);
}

int main( int argc, char **argv )
{
	long sleepsecs = 0;
	long sleepmicr = 0;
	if ( argc > 1 )
	{
		sleepsecs = atol(argv[1]);
		sleepmicr = (atof(argv[1])-sleepsecs)*1000000;
	}
	struct itimerval waiter;
	waiter.it_interval.tv_sec = 0;
	waiter.it_interval.tv_usec = 0;
	waiter.it_value.tv_sec = sleepsecs;
	waiter.it_value.tv_usec = sleepmicr;
	setitimer(ITIMER_REAL,&waiter,0);
	signal(SIGALRM,endwait);
	pause();
	return 0;
}
