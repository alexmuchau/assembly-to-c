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

void switch_case(int ** regs, Memory ** memory, Method * methods[9], int opt) {
    switch (opt) {
        case 1:
            // Instruction * instruction = inst_reader();
            char * word = "sub $3, $1, $2";
            Instruction * instruction = malloc(sizeof(Instruction));
            instruction->word = malloc(sizeof(char)*32);
            strcpy(instruction->word, word);
            instruction->next = NULL;
            
            print_spacer();
            if (get_and_validate_instructions(&instruction, methods) == 0) {
                printf("Instrução incorreta!");
            }
            
            instruction->method->execute_method(&instruction, regs, memory);
            printf("\nreg3=%i", (*regs)[3]);
            
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