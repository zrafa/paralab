/*  ./clock.c  */

/*
 * Copyright (c) 2011-2012 by
 *   Claudio Zanellato <cipotano at gmail.com>
 *   Eduardo Grosclaude <eduardo.grosclaude at gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 */
#include <sys/time.h>
#include <stdlib.h>

suseconds_t tor_clock;

//int gettimeofday(struct timeval *tv, struct timezone *tz);
//int settimeofday(const struct timeval *tv , const struct timezone *tz);
//         struct timeval {
//             time_t      tv_sec;     /* seconds */
//             suseconds_t tv_usec;    /* microseconds */
//         };

void tor_setclock();
suseconds_t tor_getelapsed();
suseconds_t tor_getclock();

void tor_setclock()
{
	tor_clock = tor_getclock();
}

suseconds_t tor_getelapsed()
{
	suseconds_t elapsed;
	elapsed = tor_getclock() - tor_clock;
	tor_setclock();
	return elapsed;
}
	
suseconds_t tor_getclock() 
{
	static struct timeval tv;
	if(gettimeofday(&tv, (struct timezone *)NULL) < 0) {
		perror("getclock");
		exit(1);
	}
	return (suseconds_t)tv.tv_sec * 1000000 + tv.tv_usec;
}


