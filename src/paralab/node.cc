/*  ./node.cc  */

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

string node::astext() { return string(""); }
string node::asdot() { return string(""); }

int node::print(int level,int maxlevel)
{
	string s;
	if(level <= maxlevel) {
		s.assign(level,' ');
		cout << s << "NODE " << astext() << endl;
	}
	return 0;
}

bool node::compare(node *n)
{
//    cout << "-------------===========-----------------------"<< endl;
//    cout << "Compare " << gettype() << ":" << n->gettype() << endl;
//    cout << "Compare " << getcall() << ":" << n->getcall() << endl;
//    cout << "Compare " << getcallsite() << ":" << n->getcallsite() << endl;
//
//
//    print(10,10);
//    n->print(10,10);
//    cout << "-------------===========-----------------------"<< endl;
	bool x = ((gettype() == n->gettype()) &&
            (getcall().compare(n->getcall()) == 0) &&
            (getcallsite() == n->getcallsite())
         );
//    cout << "RESULT " << x<< endl;
//    cout << "-------------===========-----------------------"<< endl;

    return x;
}

string node::sgetcallsite()
{
    char text[50];
	sprintf(text, "%ld",getcallsite());
	return string(text);

}

string node::getlabel()
{
    return string("NOT IMPLEMENTED!");
}
