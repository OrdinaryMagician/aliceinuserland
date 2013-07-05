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
	exit(0);
}

int main( int argc, char **argv )
{
	long sleepsecs = (argc>1)?atol(argv[1]):1;
	long sleepmicr = (argc>1)?((atof(argv[1])-sleepsecs)*1000000):0;
	struct itimerval waiter;
	waiter.it_value.tv_sec = sleepsecs;
	waiter.it_value.tv_usec = sleepmicr;
	setitimer(ITIMER_REAL,&waiter,0);
	signal(SIGALRM,endwait);
	pause();
	return 1;
}
