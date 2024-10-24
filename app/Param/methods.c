#ifndef PARAM_M_LIB
#define PARAM_M_LIB

#include "methods.h"

Param * construct_param(char * param, Param * before) {
    Param * p = malloc(sizeof(Param));
    p->param = param;
    
    if (param[0] == '$') {
        p->type = 'R';
    } else {
        p->type = 'L';
    }
    
    p->value = NULL;
    p->next = NULL;
    p->before = NULL;
}

Param ** get_head_param(Param ** p) {
    if (!(*p)->before) {
        return p;
    }
    (*p)->before->next = (*p);
    get_head_param(&((*p)->before));
}

Param * get_params(char * params) {
    Param * head_param = NULL;
    
    int spaces = 0;
    int p_length = 0;
    while (params[p_length] != '\0') {
        printf("Dentro do while\n");
        while(isspace(params[p_length]) || params[p_length] != '\0') spaces++; // trim
        params += spaces;
        spaces = 0;
        
        while(params[p_length] != ',' || params[p_length] != '\0') p_length++;
        
        if (params[p_length] == '\0') {
            break;
        }
        
        char * param = malloc(sizeof(char)*p_length);
        // printf("%s", param);
        head_param = construct_param(param, head_param);
        
        params += p_length;
        p_length = 0;
    }
    
    return *(get_head_param(&head_param));
}

#endif