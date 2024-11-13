#ifndef MEM_LIB
#define MEM_LIB

struct Address;
typedef struct Address Address;

struct Memory;
typedef struct Memory Memory;

struct Address {
    int value;
    int tag;
    
    Address * next;
};

struct Memory {
    Address * head;
    Address * tail;
    int qtd_address;
};

#endif