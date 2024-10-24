#ifndef PARAM_LIB
#define PARAM_LIB

struct Param;
typedef struct Param Param;

struct Param {
    char * param;
    char type;
    int * value;
    
    Param * next;
    Param * before;
};

#endif