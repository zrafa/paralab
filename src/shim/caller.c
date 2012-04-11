/*  ./caller.c  */

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
