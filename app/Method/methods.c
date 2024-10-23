#ifndef METH_M_LIB
#define METH_M_LIB

#include "methods.h"

int validate_r_method(char * instruction, Method * method) {
    printf("Validando método R com a instrução %s e método %s\n", instruction, method->method);
}

int validate_i_method(char * instruction, Method * method) {
    // to do
}

int validate_j_method(char * instruction, Method * method) {
    // to do
}

Method * construct_method(char * method, char type) {
    Method * m = malloc(sizeof(Method));
    
    if (m) {
        m->method = method;
        m->type = type;
        
        if (type == 'R') {
            m->validate_method = validate_r_method;
        } else if (type == 'I') {
            m->validate_method = validate_i_method;
        } else if (type == 'J') {
            m->validate_method = validate_j_method;
        }
    }
    
    return m;
}

Method * find_method(char * method, Method * methods[9]) {
    for (int i = 0; i < 9; i++) {
        if (strcmp(methods[i]->method, method) == 0) {
            return methods[i];
        }
    }
    
    return NULL;
}

#endif