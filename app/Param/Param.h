#ifndef PARAM_LIB
#define PARAM_LIB

struct Param;
typedef struct Param Param;

struct Param {
    char * param;
    
    // R = Registrador, L = Label, N = Number, M = Memory Access
    char type;
    int * value;
    
    Param * next;
    Param * before;
};

#endif