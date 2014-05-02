/*
	uname.c : Utility for ricers.
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
#define O_ALL  127

unsigned char opt = 0;

int printuname( void )
{
	/* get info */
	char kern[256], host[256], krel[256], kver[256], mach[256], proc[256];
	struct utsname libc_uname;
	if ( uname(&libc_uname) < 0 )
		return bail("uname: %s\n",strerror(errno));
	strncpy(kern,libc_uname.sysname,255);
	strncpy(host,libc_uname.nodename,255);
	strncpy(krel,libc_uname.release,255);
	strncpy(kver,libc_uname.version,255);
	strncpy(mach,libc_uname.machine,255);
	FILE *fp = fopen("/proc/cpuinfo","r");
	if ( fp )
	{
		char line[256] = {0};
		while ( !feof(fp) && strncmp(line,"model name",10) )
			fgets(line,255,fp);
		fclose(fp);
		if ( strncmp(line,"model name",10) )
			strcpy(proc,"Unknown");
		else
		{
			*strchr(line,'\n') = 0;
			strcpy(proc,strchr(line,':')+2);
		}
	}
	else strcpy(proc,"Unknown");
	// compiler is retarded, so I have to do this
	const char *fmt = " %s";
	int i = 0;
	if ( opt&O_KERN )
		printf(fmt+(i++<=0),kern);
	if ( opt&O_HOST )
		printf(fmt+(i++<=0),host);
	if ( opt&O_KREL )
		printf(fmt+(i++<=0),krel);
	if ( opt&O_KVER )
		printf(fmt+(i++<=0),kver);
	if ( opt&O_MACH )
		printf(fmt+(i++<=0),mach);
	if ( opt&O_PROC && ((opt != O_ALL) || ((opt == O_ALL)
		&& strcmp(proc,"Unknown"))) )
		printf(fmt+(i++<=0),proc);
	if ( opt&O_PLAT )
		printf(fmt+(i++<=0),mach);
	putchar('\n');
	return 0;
}

int getopts( const char *arg )
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
			opt |= O_PLAT;
			break;
		case 'm':
			opt |= O_MACH;
			break;
		case 'n':
			opt |= O_HOST;
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
		default:
			fprintf(stderr,"uname: invalid option %c\n",arg[i]);
			return 1;
		}
		i++;
	}
	return 0;
}

int main( int argc, char **argv )
{
	int i=0;
	while ( (++i<argc) && (*argv[i] == '-') )
		if ( getopts(argv[i]+1) ) return 1;
	if ( !opt ) opt |= O_KERN;
	return printuname();
}
