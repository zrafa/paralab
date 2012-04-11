/*  ./trace.cc  */

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

int trace::print(int maxlevel){
	for(iter=N.begin(); iter != N.end(); ++iter)
		(*iter)->print(0,maxlevel);
	return 0;
}

int trace::read()
{
	while(!feof(stdin)) {
		node *n = new nnode();
		if(n->read()) {
            n->setlabel(nextlabel());
			add(n);
		}

	}
	return 0;
}


int trace::doruns()
{
	int runs = 0;
	iter = N.begin();
	while(iter != N.end()) {
		if((*iter)->isrun()) {
			M.push_back(*iter);
			iter++;
		} else {
			list<node *>::iterator iter2 = iter;
			++iter2;
			if(iter2 == N.end()) {
				M.push_back(*iter);
				iter++;
			} else {
				if((*iter)->compare(*iter2)) {
					rnode *r = new rnode();
					r->setcall((*iter)->getcall());
					r->setcallsite((*iter)->getcallsite());
					r->add2run(*iter);
					while(iter2 != N.end() && (*iter)->compare(*iter2))
						r->add2run(*iter2++);
                    r->setlabel(nextlabel());
					M.push_back(r);
					runs++;
					iter = iter2;
				} else {
					M.push_back(*iter);
					iter++;
				}
			}
		}
	}
	N.swap(M);
	M.clear();
	//cout << "fin doruns, runs=" << runs << endl;
	return runs;

}

int trace::run()
{
    int runs=0, digs=0;
    do {
        runs = doruns();
//        cout << "-----------------------------------------" << endl;
//        print(10);
//        cout << "-----------------------------------------" << endl;
		digs = dodigrams();
	} while (runs || digs);
    return 0;
}

// -------------------------- DIGRAMAS ----------------------------------
bool trace::bestdigram(node *n1, node *n2)
{
    return (getmapkey().compare(digramkey(n1,n2)) == 0);
}

int trace::dodigrams()
{
	int digrams = 0;
	int replacements = 0;
	mapmax = 0;
	if((digrams = finddigrams()))
		replacements = replacedigrams();
    //cout << "fin dodigrams, digrams=" << digrams << " replacements=" << replacements << endl;
	return digrams;
}

string trace::digramkey(node *n1, node *n2)
{
    //string s = n1->getcall()+" "+n1->sgetcallsite()+"+"+n2->getcall()+" "+n2->sgetcallsite();
    char text1[50], text2[50];
    sprintf(text1, ":[%lu]", n1->getmult());
    sprintf(text2, ":[%lu]", n2->getmult());

    string s1 = n1->getcall()+" "+ n1->sgetcallsite() + string((n1->isrun())? text1 : "");
    string s2 = n2->getcall()+" "+ n2->sgetcallsite() + string((n2->isrun())? text2 : "");
	return s1 + "+" + s2;
}

// anota UN digrama en D[]
long trace::insertdigram(node *n1, node *n2)
{
	string key = digramkey(n1,n2);
	long maxk;
	//cout << "insertdigram key: " << key << " "<< "D[key]: " << D[key] << endl;
	if((maxk = ++D[key]) > mapmax) {
		mapmax = maxk;
		mapkey = key;
	}
	//cout << "part mapkey: " << mapkey << " mapmax: " << mapmax << endl;
	return maxk;
}

// recorre la traza y anota TODOS los digramas
int trace::finddigrams()
{
	int digrams = 0;
	for(iter = N.begin(); iter != N.end(); ++iter) {
		list<node *>::iterator iter2 = iter;
		if(++iter2 != N.end()) {
			insertdigram(*iter,*iter2);
            digrams++;
		}
	}
	return digrams;
}


int trace::replacedigrams()
{
	int replacements = 0;
	if(mapmax > 2) {
		for(iter = N.begin(); iter != N.end(); iter++ ) {
			list<node *>::iterator iter1 = iter;
			list<node *>::iterator iter2 = iter;
			if((++iter2 != N.end())) {
				if(bestdigram(*iter1, *iter2)) {
					dnode *d = new dnode();
					d->setlabel(nextlabel());
					d->setcall(digramkey(*iter1, *iter2));
					d->setcallsite(0L);

					d->add2digram(*iter1);
					d->add2digram(*iter2);
					M.push_back(d);
					iter++;
					replacements++;
				} else
					M.push_back(*iter);
			} else
				M.push_back(*iter);
		}
		N.swap(M);
		M.clear();
        D.clear();
	}
	return replacements;
}

int trace::printdigrams()
{
	for(map<string,long>::iterator i=D.begin(); i != D.end(); i++)
	       cout << "(" << (*i).first << ": " << (*i).second << ")" << endl;
//	cout << "Max " << mapkey << " " << mapmax << endl;
	return 0;
}

