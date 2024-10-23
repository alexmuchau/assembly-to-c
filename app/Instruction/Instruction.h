#ifndef INST_LIB
#define INST_LIB

struct Instruction;
typedef struct Instruction Instruction;

struct Instruction {
    char * data;
    Instruction * next;
};

#endif