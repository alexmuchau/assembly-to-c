#ifndef PARAM_M_LIB
#define PARAM_M_LIB

#include "methods.h"

Param * construct_param(char * param, Param * before) {
    Param * p = malloc(sizeof(Param));
    
    int len = strlen(param), count = 0;
    while((isspace(param[len - count - 1]))) count++; // trim
    
    if (count > 0) {
        param[len - count] = '\0';
    }
    
    p->param = param;
    
    if (param[0] == '$') {
        p->type = 'R';
    } else if (isdigit(param[0])) {
        // VERIFICAÇÃO SE É APENAS NÚMERO (23) OU ACESSO A MEMÓRIA 0(0X10)
        count = 0;
        while(param[count] != '(' && param[count] != '\0') count++;
        
        p->type = count == len ? 'N' : 'M';
    } else {
        p->type = 'L';
    }
    
    p->value = NULL;
    p->next = NULL;
    p->before = before;
    
    if (before) {
        before->next = p;
    }
    
    return p;
}

Param * get_head_param(Param * p) {
    if (!p->before) {
        return p;
    }
    
    return get_head_param(p->before);
}

void get_params(Instruction ** inst, char * params) {
    Param * head_param = NULL;
    
    int count = 0;
    while (params[count] != '\0') {
        while((isspace(params[count]) || params[count] == ',') && params[count] != '\0') count++; // trim
        params += count;
        count = 0;
        
        while(params[count] != ',' && params[count] != '\0') count++;
        
        char * param = malloc(sizeof(char)*count);
        strncpy(param, params, count);
        
        head_param = construct_param(param, head_param);
        (*inst)->params_qtd += 1;
        
        params += count;
        count = 0;
    }
    
    (*inst)->params = get_head_param(head_param);
}

#endif