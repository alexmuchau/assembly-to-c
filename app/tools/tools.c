#ifndef TOOLS_LIB
#define TOOLS_LIB

#include "tools.h"

void print_spacer() {
    printf("\n===========================================================\n");
}

void print_title(char * title) {
    print_spacer();
    printf("%s\n\n", title);
}

void print_footer(char * footer) {
    printf("\n%s", footer);
    print_spacer();
}

int init_menu() {
    printf("\n##########################################################\n");
    printf("--------------- Assembly to C\n");
    printf("##########################################################\n");
    int len_opts = 6;
    char opts[6][52] = {
        "Sair",
        "Inserir código e interpretador Assembly",
        "Inserir e testar código teste",
        "Ver registradores",
        "Ver código completo",
        "Rodar código completo"
    };
    for (int idx, i = 1; i <= len_opts; i++) {
        idx = i % len_opts;
        printf("%i - %s\n", idx, opts[idx]);
    }
    
    int opt = 0;
    printf("\nOpção: ");
    scanf("%i", &opt);
    printf("##########################################################\n");
    return opt;
}

Instruction * construct_example_instruction(int address) {
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
    
    word = "    add $2, $2, $3";
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

Instruction * get_last_inst(Instruction * inst) {
    if (!inst) return NULL;
    if (!inst->next) return inst;
    
    return get_last_inst(inst->next);
}

void start_execution(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label, Method * methods[11], Instruction ** head) {
    
    print_title("VALIDAÇÃO INICIADA");
    if(validate_instruction(inst, label, methods) == 0) {
        printf("ERRO NA VALIDAÇÃO!");
        exit(1);
    }
    print_footer("VALIDAÇÃO CONCLUÍDA");
    
    print_title("EXECUÇÃO INICIADA");
    execute_instructions(inst, rb, memory, label);
    print_footer("EXECUÇÃO FINALIZADA");    
    
    Instruction * last_inst = get_last_inst((*inst));
    
    if ((*head)->address == -4) (*head) = last_inst;
    else {
        (*head)->next = (*inst);
        (*inst)->before = (*head);
        (*head) = last_inst;
    }
}

void switch_case(RegBase * rb, Memory ** memory, Label ** label, Method * methods[11], Instruction ** head, int opt) {
    if (opt == 1) {
        Instruction * inst = inst_reader((*head)->address);
        if (!inst) return;
        
        start_execution(&inst, rb, memory, label, methods, head);
        
        return;
        
    } if (opt == 2){
        Instruction * inst = construct_example_instruction((*head)->address);
        
        if (!inst) return;
        
        start_execution(&inst, rb, memory, label, methods, head);
        
        return;
        
    } if (opt == 3) {
        for (int i = 0 ; i < 32; i++) {
            printf("reg%i = %i\t\t", i, rb->regs[i]);
            if (i % 3 == 0) printf("\n");
        }
        
        printf("\n\n");
        return;
        
    } if (opt == 4) {
        Instruction * main = find_inst_back(0, *head);
        print_code(main);
        
        return;
        
    } if (opt == 5) {
        Instruction * main = find_inst_back(0, *head);
        
        execute_instructions(&main, rb, memory, label);
        print_spacer();
        
        printf("EXECUÇÃO FINALIZADA!\n\n");
        return;
        
    } if (opt == 0) {
        printf("SAINDO...");
        
        return;
    }
    
    printf("WARNING - Nenhuma opção válida");
}

#endif