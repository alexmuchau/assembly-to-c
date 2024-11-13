#ifndef METH_M_LIB
#define METH_M_LIB

#include "methods.h"

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
    
    return ULA(reg_value, shift_num, "+");
}

int semantical_verification_r(Instruction * inst) {
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

int semantical_verification_i(Instruction * inst) {
    printf("Validando instrução I | %s\n", inst->word);
    
    if (inst->params_qtd < 2 || inst->params_qtd > 3) {
        printf("Quantidade incorreta (%i) de parametros da instrução (%s)", inst->params_qtd, inst->word);
        return 0;
    }
    
    Param * param = inst->params;
    
    // ADDI
    if (param->type == 'R' && param->next->type == 'R' && param->next->next->type == 'N') return 1;
    
    // LW e SW
    if (param->type == 'R' && param->next->type == 'M') return 1;
    
    // BEQ
    if (param->type == 'R' && param->next->type == 'R' && param->next->next->type == 'L') return 1;
    
    return 0;
}

int semantical_verification_j(Instruction * inst) {
    printf("Validando instrução J | %s\n", inst->word);
    
    if (inst->params_qtd > 1) return 0;
    
    if (strcmp(inst->method->method, "j") == 0 || strcmp(inst->method->method, "jal") == 0) {
        if (inst->params->type != 'L') return 0;
    } else {
        if (inst->params->type != 'R') return 0;
    }
    
    return 1;
}

Instruction * execute_r(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label) {
    // +1 por conta do $
    int dest_reg = atoi((*inst)->params->param + 1);
    int reg1 = atoi((*inst)->params->next->param + 1);
    int reg2 = atoi((*inst)->params->next->next->param + 1);
    
    int reg1_value = rb->get_reg_value(reg1, rb->regs);
    int reg2_value = rb->get_reg_value(reg2, rb->regs);
    
    if (strcmp((*inst)->method->method, "sll") == 0) {
        int value = ULA(reg1_value, reg2_value, ">>");
        rb->write_back(dest_reg, value, &(rb->regs));
        
        return (*inst)->next;
    }
    
    if (strcmp((*inst)->method->method, "add") == 0) {
        int value = ULA(reg1_value, reg2_value, "+");
        rb->write_back(dest_reg, value, &(rb->regs));
        
        return (*inst)->next;
    }
    
    if (strcmp((*inst)->method->method, "sub") == 0) {
        int value = ULA(reg1_value, reg2_value, "-");
        rb->write_back(dest_reg, value, &(rb->regs));
        
        return (*inst)->next;
    }
    
    return NULL;
}

Instruction * execute_i(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label) {
    printf("Executando instrução I | %s\n", (*inst)->word);
    
    int dest_reg = atoi((*inst)->params->param + 1);
    
    if (strcmp((*inst)->method->method, "addi") == 0) {
        int reg2 = rb->get_reg_value(atoi((*inst)->params->next->param + 1), rb->regs);
        int num = atoi((*inst)->params->next->next->param);
        
        int value = ULA(reg2, num, "+");
        rb->write_back(dest_reg, value, &(rb->regs));
        
        printf("reg%i = reg%i + %i\n\n", dest_reg, reg2, num);
        return (*inst)->next;
    }
    
    if (strcmp((*inst)->method->method, "beq") == 0) {
        int reg1 = rb->get_reg_value(dest_reg, rb->regs);
        int reg2 = rb->get_reg_value(atoi((*inst)->params->next->param + 1), rb->regs);
        
        int is_equal = ULA(reg1, reg2, "=");
        
        if (is_equal == 1) {
            printf("%i == %i = True\n\n", reg1, reg2);
            char * label_to_search = (*inst)->params->next->next->param;
            
            return get_inst_on_labels(label_to_search, (*label));
        }
        
        printf("%i == %i = False\n\n", reg1, reg2);
        return (*inst)->next;
    }
    
    int tag = get_tag((*inst)->params->next->param, rb->regs);
    Address * a = get_address(memory, (*memory)->head, tag);
    
    if (strcmp((*inst)->method->method, "lw") == 0) {
        rb->write_back(dest_reg, a->value, &(rb->regs));
        
        printf("reg%i = %i (Endereço %i)\n\n", dest_reg, a->value, a->tag);
        return (*inst)->next;
    }
    
    if (strcmp((*inst)->method->method, "sw") == 0) {
        int dest_reg_value = rb->get_reg_value(dest_reg, rb->regs);
        a->value = dest_reg_value;
        
        printf("(Endereço %i) = reg%i = %i\n\n", a->tag, dest_reg, a->value);
        return (*inst)->next;
    }
    
    return NULL;
}

Instruction * execute_j(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label) {
    printf("Executando instrução J | %s\n", (*inst)->word);
    
    if (strcmp((*inst)->method->method, "jr") == 0) {
        int reg1_value = rb->get_reg_value((atoi((*inst)->params->param)), rb->regs);
        
        if (reg1_value % 4 != 0) return NULL;
        
        Instruction * next_inst;
        if (reg1_value >= (*inst)->address) next_inst = find_inst_front(reg1_value, (*inst));
        else next_inst = find_inst_back(reg1_value, (*inst));
        
        printf("Next inst: %s\n\n", next_inst->word);
        
        return next_inst;
    }
    
    Instruction * jump_inst = get_inst_on_labels((*inst)->params->param, (*label));
    
    if (strcmp((*inst)->method->method, "jal") == 0) {
        Label * ra_label = create_new_label("ra", (*inst), (*label));
        ra_label->inst = (*inst);
    }
    
    return jump_inst->next;
    
    return jump_inst->next;
}

Method * construct_method(char * method, char type) {
    Method * m = malloc(sizeof(Method));
    
    if (m) {
        m->method = method;
        m->type = type;
        
        if (type == 'R') {
            m->semantical_verification = semantical_verification_r;
            m->execute = execute_r;
        } else if (type == 'I') {
            m->semantical_verification = semantical_verification_i;
            m->execute = execute_i;
        } else if (type == 'J') {
            m->semantical_verification = semantical_verification_j;
            m->execute = execute_j;
        }
    }
    
    return m;
}

Method * find_method(char * method, Method * methods[11]) {
    for (int i = 0; i < 9; i++) {
        if (strcmp(methods[i]->method, method) == 0) {
            return methods[i];
        }
    }
    
    return NULL;
}

#endif