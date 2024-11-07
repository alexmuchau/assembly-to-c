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

int deconstruction_instructions(Instruction ** inst, Method * methods[9]) {
    int total_length = 0;
    int len = 0;
    char * word = (*inst)->word;
    
    // trim init space
    while (isspace(word[len]) && word[len] != '\0') len++;
    
    word += len;
    
    // EXTRACTING METHOD
    len = 0;
    while (!isspace(word[len]) && word[len] != '\0') {len++; total_length++;}
    
    char * method_str = malloc(sizeof(char)*len);
    strncpy(method_str, word, len);
    
    if (word[len] != '\0') {
        word += len;
        (*inst)->method = find_method(method_str, methods);
        
        len = 0;
        while (isspace(word[len]) && word[len] != '\0') len++;
    }
    
    (*inst)->word = realloc((*inst)->word, sizeof(char)*(strlen(word)));
    
    get_params(&(*inst), word);
    
    // É LABEL
    if (!(*inst)->method) return 1;
    
    (*inst)->method->validate_method((*inst));
    return 1;
}

int validate_instruction(Instruction ** inst, Label ** label, Method * methods[9]) {    
    if (!(*inst)) return 1;
    
    if (deconstruction_instructions(inst, methods) == 0) {
        printf("Instrução incorreta!");
        return 0;
    }
    
    // Caso seja label
    if (!(*inst)->method) {
        char * label_value = clean_label((*inst)->params->param);
        
        if (label_value) create_new_label(label_value, (*inst), (*label));
    }
    
    return validate_instruction(&((*inst)->next), label, methods);
}

Instruction * execute_instructions(Instruction ** inst, int ** regs, Memory ** memory, Label ** label) {
    if (!(*inst)) return NULL;
    
    Instruction * next_inst;
    if ((*inst)->method) {
        next_inst = (*inst)->method->execute_method(inst, regs, memory, label);
    } else {
        next_inst = (*inst)->next;
    }
    
    execute_instructions(&(next_inst), regs, memory, label);
}

#endif
