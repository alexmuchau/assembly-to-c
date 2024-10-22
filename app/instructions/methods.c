#ifndef INST_M_LIB
#define INST_M_LIB

#include "methods.h"

int verify_inst(char * inst) {
    int length = strlen(inst);
    char last_char = inst[length - 2];
    
    if (last_char == '|') return 1;
}

Instruction * inst_reader() {
    printf("\n\nDIGITE SEU CÓDIGO ASSEMBLY. (o último caractere deve ser um '|')\n\n");
    
    Instruction * head = malloc(sizeof(Instruction));
    Instruction * actual_inst = head;
    size_t len = 0;
    size_t read;
    
    char * line;
    while ((read = getline(&line, &len, stdin)) != -1) {
        if (read > 0) {
            actual_inst->data = line;
            actual_inst->next = malloc(sizeof(Instruction));
            actual_inst = actual_inst->next;
            
            if (verify_inst(line) == 1) break;
        }
    }
}

#endif
