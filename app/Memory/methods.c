#ifndef MEM_M_LIB
#define MEM_M_LIB

#include "methods.h"

Address * construct_address(char * tag, int value) {
    Address * a = malloc(sizeof(Address));
    a->value = value;
    a->tag = tag;
    a->next = NULL;
}

Memory * construct_memory() {
    Memory * m = malloc(sizeof(Memory));
    m->head = NULL;
    m->tail = NULL;
    m->qtd_address = 0;
}

Address ** get_address(Memory ** m, Address * a, char * tag) {
    if (a->tag == tag) {
        return &a;
    }
    
    if (!a) {
        add_address(m, construct_address(tag, 0));
        return &((*m)->tail);
    }
    
    return get_address_value(m, a->next, tag);
}

void add_address(Memory ** m, Address * a) {
    if (!(*m)->head) {
        (*m)->head = a;
        (*m)->tail = a;
        
        return;
    }
    
    (*m)->tail->next = a;
    (*m)->tail = a;
}

#endif