#ifndef METH_M_LIB
#define METH_M_LIB

#include "methods.h"

Method * construct_method(char * method, char type) {
    Method * m = malloc(sizeof(Method));
    
    if (m) {
        m->method = method;
        m->type = type;
    }
    
    return m;
}

#endif