//////////////////////////////////////////////////

// Alex Muchau
// Assembly to C

//////////////////////////////////////////////////

#ifndef METH_H_LIB
#define METH_H_LIB

#include "../tools/libs.h"
#include "Method.h"
#include "../Instruction/methods.h"
#include "../Param/methods.h"
#include "../Hardware/Memory/methods.h"
#include "../Hardware/infraestructure.h"
#include "../Label/methods.h"

Method * construct_method(char * method, char type);
Method * find_method(char * method, Method * methods[11]);

#endif