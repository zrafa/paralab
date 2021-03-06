/*  ./rnode.cc  */

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

int rnode::add2run(node *n)
{
	L.push_back(n);
	mult++;

    time += n->gettime();
    size += n->getsize();

	for (map<string,struct profile>::iterator itr = n->P.begin(); itr != n->P.end(); ++itr) {
        string scall = itr->first;
        P[scall].size += itr->second.size;
        P[scall].time += itr->second.time;
        //cout << "rnode: call " << scall << " time=" << P[scall].time << " size=" << P[scall].size << endl;
	}

	return 0;
}

string rnode::astext()
{
	char text[500];
	sprintf(text, "LR%ld[%ld] (%lu:%lu):", label,mult, getsize(),gettime());

	string s = text;
    char text2[500];
	for (map<string,struct profile>::iterator itr = P.begin(); itr != P.end(); ++itr) {
        string s1 = itr->first;
	    struct profile p1 = itr->second;
        sprintf(text2, ":%lu:%lu", p1.size, p1.time);
	    s += "["+s1+text2+"]";
	}
    return s;
}


int rnode::print(int level,int maxlevel)
{
	string s;
	s.assign(2*level,'X');

    if(level++ <= maxlevel) {
        cout << astext() << endl;
        if(level <= maxlevel)
            for(list<node *>::iterator it = L.begin(); it != L.end(); it++) {
                if(level) {
                    string s;
                    s.assign(level,'X');
                    cout << s;
                }
                (*it)->print(level,maxlevel);
            }
	}

	return 0;
}

string rnode::asdot()
{
//    string l;
//
//
//    if(level++ <= maxlevel) {
//        l = string(label) + " ";
//        l += "[label=\"" + getlabel() + "\"]\n";
//        if(level <= maxlevel)
//            for(list<node *>::iterator it = L.begin(); it != L.end(); it++) {
//                if(level) {
//
//                    string s;
//                    s.assign(level,'X');
//                    cout << s;
//                }
//                (*it)->print(level,maxlevel);
//            }
//	}
//
//
//	char text[500];
//	sprintf(text, "LR%ld[%ld] (%lu:%lu):", label,mult, getsize(),gettime());
//
//	string s = text;
//    char text2[500];
//	for (map<string,struct profile>::iterator itr = P.begin(); itr != P.end(); ++itr) {
//        string s1 = itr->first;
//	    struct profile p1 = itr->second;
//        sprintf(text2, ":%lu:%lu", p1.size, p1.time);
//	    s += "["+s1+text2+"]";
//	}
//    return s;

//    for(list<node *>::iterator it=L.begin(); it != L.end(); it++) {
//        sprintf(text1, "%lu:%lu", (*it)->getsize(),(*it)->gettime());
//		l += "("+(*it)->getlabel() + ":" + text1 + ")";
//	}
//    return l;
//    string s = label + "[" + getlabel() + "]";
//    return s;
////1  [label="Proyecto"]
//2 [label="Alternativas de hardware"]
//1--4
//1--5
//2--3

}

string rnode::getlabel()
{
    list<node *>::iterator it;
    char text[500];

    unsigned long s=0,t=0;

    for(it = L.begin(); it != L.end(); it++) {
        s += (*it)->getsize();
        t +=  (*it)->gettime();
    }
    sprintf(text, "s=%lu:t=%lu", s,t);
    return text;
}
