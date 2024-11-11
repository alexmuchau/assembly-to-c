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
    int (*semantical_verification)(Instruction * inst);
    Instruction * (*execute)(Instruction ** inst, int ** regs, Memory ** memory, Label ** label);
};

#endif