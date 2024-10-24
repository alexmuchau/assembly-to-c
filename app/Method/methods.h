#include "Method.h"
#include "../tools/libs.h"
#include "../Instruction/Instruction.h"
#include "../Param/methods.h"

Method * construct_method(char * method, char type);
Method * find_method(char * method, Method * methods[9]);