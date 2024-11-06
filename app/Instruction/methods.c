#ifndef INST_M_LIB
#define INST_M_LIB

#include "methods.h"

int verify_inst(char * inst) {
    int length = strlen(inst);
    char last_char = inst[length - 2];
    
    if (last_char == '|') return 1;
}

Instruction * construct_inst() {
    Instruction * inst = malloc(sizeof(Instruction));
    
    inst->word = NULL;
    inst->next = NULL;
    inst->params = NULL;
    inst->params_qtd = 0;
    
    return inst;
}

Instruction * inst_reader() {
    printf("\n\nDIGITE SEU CÓDIGO ASSEMBLY. (o último caractere deve ser um '|')\n\n");
    
    Instruction * head = construct_inst();
    
    Instruction * actual_inst = head;
    size_t len = 0;
    size_t read;
    
    while (1==1) {
        char * line = malloc(sizeof(char)*32);
        while ((read = getline(&line, &len, stdin)) != -1) {
            if (read > 0) {
                actual_inst->word = line;
                actual_inst->next = construct_inst();
                actual_inst = actual_inst->next;
                break;
            }
        }
        
        if (verify_inst(line) == 1) break;
    }
    
    return head;
}

int get_and_validate_instructions(Instruction ** inst, Method * methods[9]) {
    int total_length = 0;
    int len = 0;
    char * word = (*inst)->word;
    
    // trim init space
    while (isspace(word[len])) len++;
    
    word += len;
    len = 0;
    
    // EXTRACTING METHOD
    while (!isspace(word[len])) {len++; total_length++;}
    
    char * method_str = malloc(sizeof(char)*len);
    strncpy(method_str, word, len);
    
    (*inst)->method = find_method(method_str, methods);
    
    if (!(*inst)->method) {
        printf("ERROR ON FINDING METHOD\n");
        return 0;
    }
    
    while (isspace(word[len])) len++;
    
    word += len;
    
    (*inst)->word = realloc((*inst)->word, sizeof(char)*(len+strlen(word)));
    
    get_params(&(*inst), word);
    (*inst)->method->validate_method((*inst));
    return 1;
}

void execute_instruction(Instruction ** inst, int ** regs, Memory ** memory, Method * methods[9]) {    
    if (get_and_validate_instructions(inst, methods) == 0) {
        printf("Instrução incorreta!");
        return;
    }
    
    (*inst)->method->execute_method(inst, regs, memory);
    
    if (!(*inst)->next) return;
    execute_instruction(&((*inst)->next), regs, memory, methods);
}

#endif
