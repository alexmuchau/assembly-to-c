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
    inst->data = NULL;
    inst->next = NULL;
    
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
                actual_inst->data = line;
                actual_inst->next = construct_inst();
                actual_inst = actual_inst->next;
                break;
            }
        }
        
        if (verify_inst(line) == 1) break;
    }
    
    return head;
}

int validate_instructions(Instruction * instruction, Method * methods[9]) {
    int length = strlen(instruction->data);
    instruction->data = realloc(instruction->data, length + 1);
    
    if (length < 5) {
        printf("Instrução inválida, não contém tamanho adequado");
        return 0;
    }
    
    char * inst = instruction->data;
    int char_length = 0;
    
    // EXTRACTING METHOD
    while (!isspace(inst[char_length])) char_length++;
    char * method_str = malloc(sizeof(char)*char_length);
    strncpy(method_str, inst, char_length + 1);
    
    Method * method = find_method(method_str, methods);
    
    while (isspace(inst[char_length])) char_length++;
    inst = inst + char_length;
    method->validate_method(inst, method);
}

#endif
