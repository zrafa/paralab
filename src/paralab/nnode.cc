/*  ./nnode.cc  */

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

bool nnode::read() {
	char scall[100];
	int a;
	a = scanf("%[^:]:%ld:%d:%ld:%lu:%lu ",scall,&callsite,&dest,&count,&size,&time);
	call = string(scall);
	P[call].size = size * count;
	P[call].time = time;

    return (a==6);
}

string nnode::astext()
{
	char text[500];
	sprintf(text, ":%ld:%d:%ld:%lu:%lu",getcallsite(),dest,count,size,time);
	string s = call + text;
	return s;
}

int nnode::print(int level,int maxlevel)
{
	if(level <= maxlevel) {
	    if(level) {
	        string s;
            s.assign(level,'X');
            //cout << s;
	    }
		cout << "LN" << label << astext() << endl;
	}
	return 0;
}

string nnode::asdot()
{
//    graph G {
//edge [fontname=sans,fontsize=8];
//node [fontname=sans,fontsize=10];
//ratio=compress;
//rankdir=auto;
//    for(list<node *>::iterator it=L.begin(); it != L.end(); it++) {
//        sprintf(text1, "%lu:%lu", (*it)->getsize(),(*it)->gettime());
//		l += "("+(*it)->getlabel() + ":" + text1 + ")";
//	}
//    return l;
//    string s = label + "[" + getlabel() + "]";
//    return s;
//1  [label="Proyecto"]
//2 [label="Alternativas de hardware"]
//1--4
//1--5
//2--3

}

string nnode::getlabel()
{
    return getcall()+":"+sgetcallsite();
}

//
