/*  ./dnode.h  */

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


class dnode : public node {
	list<node *> L;
	long mult;
	//long label;
  public:
	dnode() { label=0; size=0L; count=0L; time=0L; }


	string getlabel();
	unsigned long getmult(){return 0;}

    string astext();
    string asdot();
	bool isrun() { return false; };
	char gettype() { return 'D'; }

	int add2digram(node *n);
	int print(int level,int maxlevel);
};
