/*  ./nnode.h  */

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


class nnode : public node {
  public:
	nnode(){};
	bool read();
	string astext();
	string asdot();
    string getlabel();
	int print(int level,int maxlevel);
	int add2run(node *n) {return 0;}
	bool isrun() { return false; }
	char gettype() { return 'N'; }
};

