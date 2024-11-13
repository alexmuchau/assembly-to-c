#ifndef HARD_LIB
#define HARD_LIB

#include "infraestructure.h"

// Operation pode ser = { '+', '-', '>>', '<', '=', '>', '>=', '<='}
int ULA(int op1, int op2, char * operation) {
    if (strcmp(operation, "+") == 0) {
        return op1 + op2;
    }
    
    if (strcmp(operation, "-") == 0) {
        return op1 - op2;
    }
    
    if (strcmp(operation, "<") == 0) {
        return op1 < op2;
    }
    
    if (strcmp(operation, ">>") == 0) {
        return op1 >> op2;
    }
    
    if (strcmp(operation, "=") == 0) {
        return op1 == op2;
    }
    
    if (strcmp(operation, ">") == 0) {
        return op1 > op2;
    }
    
    if (strcmp(operation, ">=") == 0) {
        return op1 >= op2;
    }
    
    if (strcmp(operation, "<=") == 0) {
        return op1 <= op2;
    }
    
    printf("Operação incorreta na ULA | %i %s %i", op1, operation, op2);
    return 0;
}

int add_sp(int value, RegBase * rb) {
    rb->regs[30] = value;
    
    return 1;
}

#endif