/*  ./paralab.h  */

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
#pragma once
#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>
#include <map>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct profile {
    unsigned long size;
    unsigned long time;
};


#include "node.h"
#include "nnode.h"
#include "dnode.h"
#include "rnode.h"
#include "trace.h"


