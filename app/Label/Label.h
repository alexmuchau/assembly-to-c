//////////////////////////////////////////////////

// Alex Muchau
// Assembly to C

//////////////////////////////////////////////////

#ifndef LAB_LIB
#define LAB_LIB

struct Label;
typedef struct Label Label;

#include "../Instruction/Instruction.h"
struct Label {
    char * value;
    Instruction * inst;
    
    Label * next;
};

#endif