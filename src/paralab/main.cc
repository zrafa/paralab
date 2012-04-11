/*  ./main.cc  */

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

#include "paralab.h"

int procesar(int level)
{
	trace t;

	t.read();
	t.run();
	t.print(level);
	return 0;
}
//-----------------------------------------------------------------

int main(int argc, char *argv[])
{
    if(argc < 2) {
        cout << "Falta nivel de profundidad" << endl;
        return 0;
    }
    procesar(atoi(argv[1]));
}
