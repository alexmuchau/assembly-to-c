#ifndef TOOLS_LIB
#define TOOLS_LIB

#include "tools.h"

int print_header_spacer() {
    printf("###############################\n");
}

int print_spacer() {
    printf("\n-------------\n\n");
}

int init_menu() {
    print_header_spacer();
    printf("(1) - Escrever instrução\n(2) - Ver registradores\n(3) - Ver código completo\n(0) - Sair\n");
    print_header_spacer();
    
    int opt = 0;
    scanf("%i", &opt);
    
    if (opt > 3) {
        printf("WARNING - Nenhuma opção válida");
    };
    
    return opt;
}

void switch_case(int ** regs, Memory ** memory, Label ** label, Method * methods[9], int opt) {
    switch (opt) {
        case 1:
            // Instruction * instruction = inst_reader();
            char * word = "TESTE:";
            Instruction * instruction = malloc(sizeof(Instruction));
            instruction->word = malloc(sizeof(char)*32);
            strcpy(instruction->word, word);
            instruction->next = NULL;
            // char * word = "addi $2, $0, 23";
            // Instruction * instruction = malloc(sizeof(Instruction));
            // instruction->word = malloc(sizeof(char)*32);
            // strcpy(instruction->word, word);
            
            // word = "sw $2, 0($2)";
            // instruction->next = malloc(sizeof(Instruction));
            // instruction->next->word = malloc(sizeof(char)*32);
            // strcpy(instruction->next->word, word);
            
            // word = "lw $3, 0($2)";
            // instruction->next->next = malloc(sizeof(Instruction));
            // instruction->next->next->word = malloc(sizeof(char)*32);
            // strcpy(instruction->next->next->word, word);
            
            execute_instruction(&instruction, regs, memory, label, methods);
            break;
        case 2:
            printf("Opção 2");
            
            break;
        case 3:
            printf("Opção 3");
            
            break;
        case 0:
            printf("Opção 0");
            
            break;
        default:
            printf("WARNING - Nenhuma opção válida");
            break;
    }
}

#endif