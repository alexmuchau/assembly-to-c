#include "tools/libs.h"
#include "tools/tools.h"
#include "Method/methods.h"

int main() {
    int * regs = malloc(sizeof(int)*32);
    Method * methods[9] = {
        construct_method("add", 'R'),
        construct_method("sub", 'R'),
        construct_method("sll", 'R'),
        construct_method("addi", 'I'),
        construct_method("lw", 'I'),
        construct_method("sw", 'I'),
        construct_method("j", 'J'),
        construct_method("jal", 'J'),
        construct_method("jr", 'J'),
    };
    int opt = 1;
    
    while (opt != 0) {
        // opt = init_menu();
        switch_case(regs, methods, opt);
    }
}