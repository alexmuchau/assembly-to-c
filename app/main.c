#include "tools/libs.h"
#include "tools/tools.h"
#include "Method/methods.h"

int main() {
    int regs[32] = {0};
    
    regs[1] = 0x12;
    regs[2] = 8;
    
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
    unsigned int *fixed_address = (unsigned int *)0x12345678;
    // *fixed_address = 12;
    
    printf("%u", *fixed_address);
    
    // while (opt != 0) {
        // opt = init_menu();
        // switch_case(&regs, methods, opt);
    // }
}