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
    // printf("Validando instrução R | %s\n", inst->word);
    
    if (inst->params_qtd != 3) {
        printf("Quantidade incorreta (%i) de parametros da instrução (%s)", inst->params_qtd, inst->word);
        return 0;
    }
    
    Param * param = inst->params;
    
    if (param->type != 'R' && param->next->type != 'R' && (param->next->next->type != 'R' && param->next->next->type != 'N')) {
        printf("Parametrização incorreta da instrução (%s)", inst->word);
        return 0;
    }
}

int semantical_verification_i(Instruction * inst) {
    // printf("Validando instrução I | %s\n", inst->word);
    
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
    // printf("Validando instrução J | %s\n", inst->word);
    
    if (inst->params_qtd > 1) return 0;
    
    if (strcmp(inst->method->method, "j") == 0 || strcmp(inst->method->method, "jal") == 0) {
        if (inst->params->type != 'L') return 0;
    } else {
        if (inst->params->type != 'R') return 0;
    }
    
    return 1;
}

Instruction * execute_r(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label) {
    char * cleaned_word = trim_word((*inst)->word);
    printf("\n%s (%d)------------------->\n", cleaned_word, (*inst)->address);
    
    int rs = 0, rt = 0, rd = 0, shamt = 0, funct = 0;
    
    rd = atoi((*inst)->params->param + 1);
    rs = atoi((*inst)->params->next->param + 1);
    
    int rs_value = rb->get_reg_value(rs, rb->regs);
    
    if (strcmp((*inst)->method->method, "sll") == 0) {
        shamt = atoi((*inst)->params->next->next->param + 1);
        
        int value = ULA(rs_value, shamt, ">>");
        rb->write_back(rd, value, &(rb->regs));
        
        printf("reg%d = (reg%d)%d >> %d = %d\n", rd, rs, rs_value, shamt, value);
        
    } else {
        rt = atoi((*inst)->params->next->next->param + 1);
        int rt_value = rb->get_reg_value(rt, rb->regs);
        
        if (strcmp((*inst)->method->method, "add") == 0) {
            int value = ULA(rs_value, rt_value, "+");
            rb->write_back(rd, value, &(rb->regs));
            
            printf("reg%d = (reg%d)%d + (reg%d)%d = %d\n", rd, rs, rs_value, rt, rt_value, value);
        } else if (strcmp((*inst)->method->method, "sub") == 0) {
            int value = ULA(rs_value, rt_value, "-");
            rb->write_back(rd, value, &(rb->regs));
            
            printf("reg%d = (reg%d)%d - (reg%d)%d = %d\n", rd, rs, rs_value, rt, rt_value, value);
        }
    }
    
    printf("  | %12s  | %5s | %5s | %5s | %5s | %5s |\n", "Cód da Inst", "rs", "rt", "rd", "Shamt", "Funct");
    printf("R | %-12s | %5d | %5d | %5d | %5d | %5d |\n", (*inst)->method->method, rs, rt, rd, shamt, funct);
    printf("----------------------------------------------------------------|\n\n");
    return (*inst)->next;;
}

Instruction * execute_i(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label) {
    char * cleaned_word = trim_word((*inst)->word);
    printf("\n%s (%d)------------------->\n", cleaned_word, (*inst)->address);
    
    int rt = atoi((*inst)->params->param + 1), rs = 0, imed = 0;
    
    Instruction * next_inst;
    if (strcmp((*inst)->method->method, "addi") == 0) {
        rs = atoi((*inst)->params->next->param + 1);
        int rs_value = rb->get_reg_value(rs, rb->regs);
        imed = atoi((*inst)->params->next->next->param);
        
        int value = ULA(rs_value, imed, "+");
        rb->write_back(rt, value, &(rb->regs));
        
        printf("reg%i = reg%i + %i\n", rt, rs, imed);
        
    } else if (strcmp((*inst)->method->method, "beq") == 0) {
        rs = atoi((*inst)->params->next->param + 1);
        int rt_value = rb->get_reg_value(rt, rb->regs);
        int rs_value = rb->get_reg_value(rs, rb->regs);
        char * label_to_search = (*inst)->params->next->next->param;
        next_inst = get_inst_on_labels(label_to_search, (*label));
        imed = next_inst->address;
        
        int is_equal = ULA(rt_value, rs_value, "=");
        
        if (is_equal == 0) next_inst = (*inst)->next;
             
        printf("%i == %i = %d\n", rt_value, rs_value, is_equal);
    } else {
        imed = get_tag((*inst)->params->next->param, rb->regs);
        Address * a = get_address(memory, (*memory)->head, imed);
        
        if (strcmp((*inst)->method->method, "lw") == 0) {
            rb->write_back(rt, a->value, &(rb->regs));
            
            printf("reg%i = %i (Endereço %i)\n", rt, a->value, a->tag);
            next_inst = (*inst)->next;
            
        } else if (strcmp((*inst)->method->method, "sw") == 0) {
            int rt_value = rb->get_reg_value(rt, rb->regs);
            a->value = rt_value;
            
            printf("(Endereço %i) = reg%i = %i\n", a->tag, rt, a->value);
            next_inst = (*inst)->next;
        }   
    }
    
    printf("  | %12s  | %5s | %5s | %22s |\n", "Cód da Inst", "rs", "rt", "Endereço Imediato");
    printf("I | %-12s | %5d | %5d | %21d |\n", (*inst)->method->method, rs, rt, imed);
    printf("----------------------------------------------------------------|\n\n");
    
    return next_inst;
}

Instruction * execute_j(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label) {
    char * cleaned_word = trim_word((*inst)->word);
    printf("\n%s (%d)------------------->\n", cleaned_word, (*inst)->address);
    
    Instruction * jump_inst;
    if (strcmp((*inst)->method->method, "jr") == 0) {
        int reg1_value = rb->get_reg_value((atoi((*inst)->params->param)), rb->regs);
        
        if (reg1_value % 4 != 0) {
            printf("ERRO - Endereço incorreto %i (não é múltiplo de 4)\n", reg1_value);
            return NULL;
        }
        
        if (reg1_value >= (*inst)->address) jump_inst = find_inst_front(reg1_value, (*inst));
        else jump_inst = find_inst_back(reg1_value, (*inst));
        
    } else {
        jump_inst = get_inst_on_labels((*inst)->params->param, (*label));
        
        if (strcmp((*inst)->method->method, "jal") == 0) {
            Label * ra_label = create_new_label("ra", (*inst), (*label));
            ra_label->inst = (*inst);
        }
    }
    
    printf("Jumping para instrução %s\n", jump_inst->word);
    printf("  | %12s  | %38s |\n", "Cód da Inst", "Endereço");
    printf("J | %-12s | %37d |\n", (*inst)->method->method, jump_inst->address);
    printf("----------------------------------------------------------------|\n\n");
    return jump_inst;
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