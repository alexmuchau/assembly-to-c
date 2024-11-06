#ifndef METH_M_LIB
#define METH_M_LIB

#include "methods.h"
#include "../Label/methods.h"

int get_tag(char * tag, int * regs) {
    int len = 0;
    while (tag[len] != '(') len++;
    char * c = malloc(sizeof(char)*len);
    strncpy(c, tag, len);
    int shift_num = atoi(c);
    
    free(c);
    
    // Jumping $
    tag += len + 2;
    len = 0;
    while (tag[len] != ')') len++;
    c = malloc(sizeof(char)*len);
    strncpy(c, tag, len);
    int reg_value = regs[atoi(c)];
    
    free(c);
    
    return reg_value + shift_num;
}

int validate_r_method(Instruction * inst) {
    // Caso o tamanho da string parâmetro for menor que o mínimo de 2 parâmetros mais o espaço
    printf("Validando instrução R | %s\n", inst->word);
    
    if (inst->params_qtd != 3) {
        printf("Quantidade incorreta (%i) de parametros da instrução (%s)", inst->params_qtd, inst->word);
        return 0;
    }
    
    Param * param = inst->params;
    
    if (param->type != 'R' && param->next->type != 'R' && (param->next->next->type != 'R' && param->next->next->type != 'M')) {
        printf("Parametrização incorreta da instrução (%s)", inst->word);
        return 0;
    }
}

int validate_i_method(Instruction * inst) {
    printf("Validando instrução I | %s\n", inst->word);
    
    if (inst->params_qtd < 2 || inst->params_qtd > 3) {
        printf("Quantidade incorreta (%i) de parametros da instrução (%s)", inst->params_qtd, inst->word);
        return 0;
    }
    
    Param * param = inst->params;
    
    // ADDI
    if (param->type == 'R' && param->next->type == 'R' && param->next->next->type == 'N') {
        return 1;
    }
    
    // LW e SW
    if (param->type == 'R' && param->next->type == 'M') {
        return 1;
    }
    
    return 0;
}

int validate_j_method(Instruction * inst) {
    printf("Validando instrução I | %s\n", inst->word);
    
    if (inst->params_qtd > 1) return 0;
    
    if (strcmp(inst->method->method, "j") == 0 || strcmp(inst->method->method, "jal") == 0) {
        if (inst->params->type != 'L') return 0;
    } else {
        if (inst->params->type != 'R') return 0;
    }
    
    return 1;
}

int execute_r_method(Instruction ** inst, int ** regs, Memory ** memory, Label ** label) {
    // +1 por conta do $
    int dest_reg = atoi((*inst)->params->param + 1);
    int op1_reg = atoi((*inst)->params->next->param + 1);
    
    if (strcmp((*inst)->method->method, "sll") == 0) {
        int op2 = atoi((*inst)->params->next->next->param);
        printf("Executando ssl com:\ndest =%i\nreg=%i\nnum=%i", dest_reg, op1_reg, op2);
        
        (*regs)[dest_reg] = (*regs)[op1_reg] << op2;
        return 1;
    }
    
    int op2_reg = atoi((*inst)->params->next->next->param + 1);
    printf("Executando %s com:\ndest=%i\nreg1=%i\nreg2=%i", (*inst)->method->method, dest_reg, op1_reg, op2_reg);
    
    if (strcmp((*inst)->method->method, "add") == 0) {
        (*regs)[dest_reg] = (*regs)[op1_reg] - (*regs)[op2_reg];
        return 1;
    }
    
    if (strcmp((*inst)->method->method, "sub") == 0) {
        (*regs)[dest_reg] = (*regs)[op1_reg] - (*regs)[op2_reg];
        return 1;
    }
    
    return 0;
}

int execute_i_method(Instruction ** inst, int ** regs, Memory ** memory, Label ** label) {
    printf("Executando instrução I | %s\n", (*inst)->word);
    
    int reg1 = atoi((*inst)->params->param + 1);
    
    if (strcmp((*inst)->method->method, "addi") == 0) {
        int reg2 = atoi((*inst)->params->next->param + 1);
        int num = atoi((*inst)->params->next->next->param);
        
        (*regs)[reg1] = (*regs)[reg2] + num;
        
        printf("reg%i = reg%i + %i\n\n", reg1, reg2, num);
        return 1;
    }
    
    int tag = get_tag((*inst)->params->next->param, (*regs));
    Address * a = get_address(memory, (*memory)->head, tag);
    
    if (strcmp((*inst)->method->method, "lw") == 0) {
        (*regs)[reg1] = a->value;
        
        printf("reg%i = %i (Endereço %i)\n\n", reg1, a->value, a->tag);
        return 1;
    }
    
    if (strcmp((*inst)->method->method, "sw") == 0) {
        a->value = (*regs)[reg1];
        
        printf("(Endereço %i) = reg%i = %i\n\n", a->tag, reg1, a->value);
        return 1;
    }
    
    return 0;
}

int execute_j_method(Instruction ** inst, int ** regs, Memory ** memory, Label ** label) {
    printf("Executando instrução J | %s\n", (*inst)->word);
}

Method * construct_method(char * method, char type) {
    Method * m = malloc(sizeof(Method));
    
    if (m) {
        m->method = method;
        m->type = type;
        
        if (type == 'R') {
            m->validate_method = validate_r_method;
            m->execute_method = execute_r_method;
        } else if (type == 'I') {
            m->validate_method = validate_i_method;
            m->execute_method = execute_i_method;
        } else if (type == 'J') {
            m->validate_method = validate_j_method;
            m->execute_method = execute_j_method;
        }
    }
    
    return m;
}

Method * find_method(char * method, Method * methods[9]) {
    // printf("Encontrando método %s com tamanho %li\n", method, strlen(method));
    for (int i = 0; i < 9; i++) {
        if (strcmp(methods[i]->method, method) == 0) {
            return methods[i];
        }
    }
    // printf("Falha para encontrar método\n");
    
    return NULL;
}

#endif