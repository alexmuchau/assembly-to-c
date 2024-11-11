#ifndef METH_M_H
#define METH_M_H

#include "Method.h"
#include "../tools/libs.h"
#include "../Instruction/methods.h"
#include "../Param/methods.h"
#include "../Memory/methods.h"

Method * construct_method(char * method, char type);
Method * find_method(char * method, Method * methods[11]);

#endif