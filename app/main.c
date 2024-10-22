#include "tools/libs.h"
#include "instructions/instructions.h"

int init_menu() {
    printf("###############################\n");
    printf("(1) - Escrever instrução\n(2) - Ver registradores\n(3) - Ver código completo\n(0) - Sair\n");
    printf("###############################\n");
    
    int opt = 0;
    scanf("%i", &opt);
    
    if (opt > 3) {
        printf("WARNING - Nenhuma opção válida");
    };
    
    return opt;
}

int switch_case(int *regs, int opt) {
    switch (opt) {
        case 1:
            inst_reader();
            return 0;
            
        case 2:
            printf("Opção 2");
            return 0;
            
        case 3:
            printf("Opção 3");
            return 0;
            
        case 0:
            printf("Opção 0");
            return 1;
            
        default:
            printf("WARNING - Nenhuma opção válida");
            return 0;
    }
}

int main() {
    int * regs = malloc(sizeof(int)*32);
    int is_exit = 0;
    
    while (is_exit == 0) {
        int opt = init_menu();
        is_exit = switch_case(regs, opt);
    }
}