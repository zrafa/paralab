/*  ./node.h  */

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


class node {
  public:
    long label;
	node(){};

	map<string,struct profile> P;
	string call;
	long callsite;

	string getcall(){return call;}
	int setcall(string s){call = s; return 0;}
	long getcallsite(){return callsite;}
	string sgetcallsite();
	int setcallsite(long c){callsite = c; return 0;}

	int dest;
	unsigned long count;
	unsigned long time;
	unsigned long size;
	unsigned long gettime() { return time; }
	unsigned long getsize() { return (count)? count * size : size; }
	//int setsize(long m) {size = m; return 0;}
	int addtime(long m) {return 0;}
	int addsize(long m) {return 0;}

    virtual unsigned long getmult(){return 0;}
	virtual bool compare(node *n);
	virtual int add2run(node *n){return 0;};
	virtual char gettype() { return 'X'; }
	virtual string astext();
	virtual string getlabel();
	int setlabel(long l) { label=l; return 0;}
	virtual int print(int level,int maxlevel);
	virtual bool isrun(){return false;}
	virtual bool read(){return true;}
	virtual string asdot();
};

