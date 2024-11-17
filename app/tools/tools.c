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

Instruction * construct_example_instruction() {
    int address = -4;
    char * word = "WHILE:";
    Instruction * instruction = malloc(sizeof(Instruction));
    instruction->word = malloc(sizeof(char)*32);
    strcpy(instruction->word, word);
    address = instruction->address = address + 4;
    
    word = "    beq $1, $2, FIM";
    instruction->next = malloc(sizeof(Instruction));
    instruction->next->word = malloc(sizeof(char)*32);
    strcpy(instruction->next->word, word);
    address = instruction->next->address = address + 4;
    instruction->next->before = instruction;
    
    word = "    addi $2, $2, 2";
    instruction->next->next = malloc(sizeof(Instruction));
    instruction->next->next->word = malloc(sizeof(char)*32);
    strcpy(instruction->next->next->word, word);
    address = instruction->next->next->address = address + 4;
    instruction->next->next->before = instruction->next;
    
    word = "    jr $4";
    instruction->next->next->next = malloc(sizeof(Instruction));
    instruction->next->next->next->word = malloc(sizeof(char)*32);
    strcpy(instruction->next->next->next->word, word);
    address = instruction->next->next->next->address = address + 4;
    instruction->next->next->next->before = instruction->next->next;
    
    word = "FIM:";
    instruction->next->next->next->next = malloc(sizeof(Instruction));
    instruction->next->next->next->next->word = malloc(sizeof(char)*32);
    strcpy(instruction->next->next->next->next->word, word);
    address = instruction->next->next->next->next->address = address + 4;
    instruction->next->next->next->next->before = instruction->next->next->next;
    
    return instruction;
}

void switch_case(RegBase * rb, Memory ** memory, Label ** label, Method * methods[11], int opt) {
    switch (opt) {
        case 1:
            Instruction * inst;
            
            inst = (*label)->inst->next = inst_reader((*label)->inst->address);
            // inst = construct_example_instruction();
            
            if(validate_instruction(&inst, label, methods) == 0) {
                return;
            }
            
            
            printf("\nVALIDAÇÃO CONCLUÍDA");
            print_spacer();
            
            Instruction * last_inst = execute_instructions(&inst, rb, memory, label);
            print_spacer();
            
            if (!last_inst) {
                printf("ERRO NA EXECUÇÃO!\n\n");
                return;
            }
            
            printf("EXECUÇÃO FINALIZADA!\n\n");
            Label * last_inst_label = construct_label("LASTINSTRUCTION", last_inst);
            
            last_inst_label->next = (*label)->next;
            
            (*label) = last_inst_label;
            
            break;
        case 2:
            for (int i = 0 ; i < 32; i++) {
                printf("reg%i = %i\t\t", i, rb->regs[i]);
                if (i % 3 == 0) printf("\n");
            }
            
            printf("\n");
            break;
        case 3:
            print_code((*label)->inst);
            
            break;
        case 0:
            printf("SAINDO...");
            
            break;
        default:
            printf("WARNING - Nenhuma opção válida");
            break;
    }
}

#endif