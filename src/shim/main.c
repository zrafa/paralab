/*  ./main.c  */

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
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <stdlib.h>
#include <stdio.h>

unw_word_t caller()
{
	unw_cursor_t cursor;
	unw_word_t sp;
	unw_context_t uc;

	unw_getcontext(&uc);
	unw_init_local(&cursor, &uc);
	if(unw_step (&cursor) > 0  && unw_step (&cursor) > 0) {
		unw_get_reg(&cursor, UNW_REG_SP, &sp);
		return sp;
	} else {
		perror("caller");
		exit(1);
	}
}

unw_word_t current()
{
	unw_cursor_t cursor;
	unw_word_t ip,sp;
	unw_context_t uc;

	unw_getcontext(&uc);
	unw_init_local(&cursor, &uc);
        if(unw_step (&cursor) > 0) {
		unw_get_reg(&cursor, UNW_REG_IP, &ip);
		unw_get_reg(&cursor, UNW_REG_SP, &sp);
		printf("ip %lx sp %lx\n",ip,sp);
        	unw_step (&cursor);
		unw_get_reg(&cursor, UNW_REG_IP, &ip);
		unw_get_reg(&cursor, UNW_REG_SP, &sp);
		printf("---ip %lx sp %lx\n",ip,sp);
		printf("------------------\n");
	}
}


int otro() 
{
	int i,a;
	unw_word_t c;

	c=current();
	for(i=0; i<10; i++) 
		a += 2*i;
	c=current();
}


int main(int argc, char *argv[]) {
	int i,a;
	unw_word_t c;

	c=current(); 
	for(i=0; i<10; i++) 
		a += 2*i;
	
	c=current();
	for(i=0; i<10; i++) 
		a += 2*a*i;
	
	otro();
}

