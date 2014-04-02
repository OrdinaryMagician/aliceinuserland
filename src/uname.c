/*
	uname.c : Brag about your kernel.
	(C)2012-2014 Marisa Kirisame, UnSX Team.
	Part of Au, the Alice in Userland project.
	Released under the MIT License.
*/
#include <sys/utsname.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include "helpers.h"
#define O_KERN 1
#define O_HOST 2
#define O_KREL 4
#define O_KVER 8
#define O_MACH 16
#define O_PROC 32
#define O_PLAT 64
#define O_OPER 128
#define O_ALL  255
#if defined(__aliceos__)
# define OSNAME "AliceOS"
#elif defined(__linux__)||defined(linux)||defined(__linux)
# if defined(__ANDROID__)
#  define OSNAME "Android"
# elif defined(__gnu_linux__)&&!defined(OVERRIDE_GNU)
#  define OSNAME "GNU/Linux"
# else
#  define OSNAME "Linux"
# endif
#elif defined(_WIN32)
# if defined(__CYGWIN__)
#  define OSNAME "Cygwin"
# else
#  define OSNAME "Windows"
# endif
#elif defined(__FreeBSD__)
# if defined(__GLIBC__)&&!defined(OVERRIDE_GNU)
#  define OSNAME "GNU/kFreeBSD"
# else
#  define OSNAME "FreeBSD"
# endif
#elif defined(__APPLE__)&&defined(__MACH__)
# define OSNAME "Mac OS X"
#elif defined(__sun)||defined(sun)
# if defined(__SVR4)||defined(__svr4__)
#  define OSNAME "Solaris"
# else
#  define OSNAME "SunOS"
# endif
#elif defined(AMIGA)||defined(__amigaos__)
# define OSNAME "AmigaOS"
#elif defined(__BEOS__)
# define OSNAME "BeOS"
#elif defined(__NetBSD__)
# define OSNAME "NetBSD"
#elif defined(__OpenBSD__)
# define OSNAME "OpenBSD"
#elif defined(__DragonFly__)
# define OSNAME "DragonFly BSD"
#elif defined(EPLAN9)
# define OSNAME "Plan 9"
#elif defined(__minix)
# define OSNAME "Minix"
#elif defined(__GNU__)||defined(__gnu_hurd__)
# define OSNAME "Hurd"
#else
# define OSNAME "Unknown"
#endif

unsigned char opt = 0;

typedef struct
{
	char kern[256];
	char host[256];
	char krel[256];
	char kver[256];
	char mach[256];
	char proc[256];
	char oper[256];
} uname_t;
uname_t au_uname = {{0},{0},{0},{0},{0},{0},{0}};

void getuname( void )
{
	struct utsname libc_uname;
	if ( uname(&libc_uname) < 0 )
		exit(bail("uname: %s\n",strerror(errno)));
	strncpy(au_uname.kern,libc_uname.sysname,255);
	strncpy(au_uname.host,libc_uname.nodename,255);
	strncpy(au_uname.krel,libc_uname.release,255);
	strncpy(au_uname.kver,libc_uname.version,255);
	strncpy(au_uname.mach,libc_uname.machine,255);
	FILE *fp = fopen("/proc/cpuinfo","r");
	if ( fp )
	{
		char line[256] = {0};
		while ( !feof(fp) && strncmp(line,"model name",10) )
			fgets(line,255,fp);
		fclose(fp);
		if ( strncmp(line,"model name",10) )
			strcpy(au_uname.proc,"Unknown");
		else
		{
			*strchr(line,'\n') = 0;
			strcpy(au_uname.proc,strchr(line,':')+2);
		}
	}
	else strcpy(au_uname.proc,"Unknown");
	strcpy(au_uname.oper,OSNAME);
}

void printuname( void )
{
	int i = 0;
	// compiler is retarded, so I have to do this
	const char *fmt = " %s";
	if ( opt&O_KERN )
		printf(fmt+(i++<=0),au_uname.kern);
	if ( opt&O_HOST )
		printf(fmt+(i++<=0),au_uname.host);
	if ( opt&O_KREL )
		printf(fmt+(i++<=0),au_uname.krel);
	if ( opt&O_KVER )
		printf(fmt+(i++<=0),au_uname.kver);
	if ( opt&O_MACH )
		printf(fmt+(i++<=0),au_uname.mach);
	if ( opt&O_PROC && ((opt != O_ALL) || ((opt == O_ALL)
		&& strcmp(au_uname.proc,"Unknown"))) )
		printf(fmt+(i++<=0),au_uname.proc);
	if ( opt&O_PLAT )
		printf(fmt+(i++<=0),au_uname.mach);
	if ( opt&O_OPER )
		printf(fmt+(i++<=0),au_uname.oper);
	putchar('\n');
}

void getopts( const char *arg )
{
	int i = 0;
	while ( arg[i] != 0 )
	{
		switch ( arg[i] )
		{
		case 'a':
			opt |= O_ALL;
			break;
		case 'i':
		case 'M':
			opt |= O_PLAT;
			break;
		case 'm':
			opt |= O_MACH;
			break;
		case 'n':
			opt |= O_HOST;
			break;
		case 'o':
			opt |= O_OPER;
			break;
		case 'p':
			opt |= O_PROC;
			break;
		case 'r':
			opt |= O_KREL;
			break;
		case 's':
			opt |= O_KERN;
			break;
		case 'v':
			opt |= O_KVER;
			break;
		}
		i++;
	}
}

int main( int argc, char **argv )
{
	int i=1;
	getuname();
	while ( i<argc )
	{
		if ( (argv[i][0] == '-') && isin(argv[i][1],"aiMmnoprsv") )
			getopts(argv[i]+1);
		i++;
	}
	if ( !opt ) opt |= O_KERN;
	printuname();
	return 0;
}
