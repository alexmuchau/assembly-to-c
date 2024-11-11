#ifndef INST_LIB
#define INST_LIB

struct Instruction;
typedef struct Instruction Instruction;

#include "../Method/Method.h"
#include "../Param/Param.h"

struct Instruction {
    char * word;
    Instruction * next;
    Instruction * before;
    int address;
    
    Method * method;
    Param * params;
    int params_qtd;
};

#endif