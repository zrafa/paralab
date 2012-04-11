/*  ./trace.h  */

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

class trace {
	list<node *> N;
	list<node *> M;
	map<string,long> D;
	list<node *>::iterator iter;
	long mapmax;
	long label;
	string mapkey;
  public:
	trace() { label = 0L; };
	long nextlabel() {return label++;};
	struct NodeCompare {
		bool operator()(node *n1, node *n2)
		{
			return n1->compare(n2);
		}
	};
	int read();
	bool bestdigram(node *n1, node *n2);
	long insertdigram(node *n1, node *n2);
	string digramkey(node *n1, node *n2);
	string getmapkey() { return mapkey; };
	int finddigrams();
	int printdigrams();
	int replacedigrams();
	int dodigrams();
	int add(node *n){ N.push_back(n); return 0;}
	int print(int maxlevel);
	int run();
	int doruns();
};
