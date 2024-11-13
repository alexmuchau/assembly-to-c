#ifndef REG_M_LIB
#define REG_M_LIB

#include "methods.h"

int get_reg_value(int reg, int regs[32]) {
    return regs[reg];
}

int write_back(int reg, int value, int (*regs)[32]) {
    (*regs)[reg] = value;
    
    return 1;
}

RegBase * construct_reg_base() {
    RegBase * rb = malloc(sizeof(RegBase));
    
    memset(rb->regs, 0, sizeof(rb->regs));
    
    rb->get_reg_value = get_reg_value;
    rb->write_back = write_back;
    
    return rb;
}

#endif