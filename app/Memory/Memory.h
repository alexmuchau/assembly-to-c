#ifndef MEM_LIB
#define MEM_LIB

#include "../tools/libs.h"

struct Address;
typedef struct Address Address;

struct Address {
    int value;
    char * tag;
    
    Address * next;
};

struct Memory;
typedef struct Memory Memory;

struct Memory {
    Address * head;
    Address * tail;
    int qtd_address;
};

#endif