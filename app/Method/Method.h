#ifndef METH_LIB
#define METH_LIB

struct Method;
typedef struct Method Method;

#include "../Instruction/Instruction.h"
#include "../Hardware/Memory/Memory.h"
#include "../Label/Label.h"
#include "../Hardware/RegBase/RegBase.h"

struct Method {
    char * method;
    char type;
    int (*semantical_verification)(Instruction * inst);
    Instruction * (*execute)(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label);
};

#endif