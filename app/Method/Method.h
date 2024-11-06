#ifndef METH_LIB
#define METH_LIB

struct Method;
typedef struct Method Method;

#include "../Instruction/Instruction.h"
#include "../Memory/Memory.h"
#include "../Label/Label.h"

struct Method {
    char * method;
    char type;
    int (*validate_method)(Instruction * inst);
    int (*execute_method)(Instruction ** inst, int ** regs, Memory ** memory, Label ** label);
};

#endif