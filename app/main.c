#include "tools/libs.h"
#include "tools/tools.h"

#include "Method/methods.h"
#include "Instruction/methods.h"

#include "Label/methods.h"
#include "Hardware/infraestructure.h"

int main() {
    RegBase * reg_base = construct_reg_base();
    Memory * memory = construct_memory();
    Label * label = construct_label("MAIN:", construct_inst(NULL));
    
    reg_base->write_back(1, 12, &(reg_base->regs));
    reg_base->write_back(2, 8, &(reg_base->regs));
    
    Method * methods[11] = {
        construct_method("add", 'R'),
        construct_method("sub", 'R'),
        construct_method("sll", 'R'),
        construct_method("addi", 'I'),
        construct_method("lw", 'I'),
        construct_method("sw", 'I'),
        construct_method("beq", 'I'),
        construct_method("j", 'J'),
        construct_method("jr", 'J'),
        construct_method("jal", 'J'),
    };
    int opt = 1;
    
    while (opt != 0) {
        opt = init_menu();
        switch_case(reg_base, &memory, &label, methods, opt);
    }
}