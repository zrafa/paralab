/*  ./rnode.h  */

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


class rnode : public node {
	list<node *> L;
	//map<string,struct profile> P;
	unsigned long mult;
  public:
	rnode() { mult = 0L; time=0L; count=0L; size=0L;}
	unsigned long getmult() {return mult;}
	int add2run(node *n);
	bool isrun() { return true; };
	string astext();
	string asdot();
	string getlabel();

	int print(int level,int maxlevel);
	char gettype() { return 'R'; }
};
