#ifndef METH_M_LIB
#define METH_M_LIB

#include "methods.h"

int params_length_validate(char * params, int min_qty_params) {
    int params_length = strlen(params);
    
    int space_length = 1;
    int min_param_length = 2;
    int min_params_length = (space_length * (min_qty_params - 1)) + (min_param_length * min_qty_params);
    
    // printf("params_length < min_params_length: %i < %i\n", params_length, min_params_length);
    
    return params_length > min_params_length;
}

int validate_r_method(char * str_params, Method * method) {
    // Caso o tamanho da string parâmetro for menor que o mínimo de 2 parâmetros mais o espaço
    printf("Parametros (%s) | Validando método R com o método %s\n", str_params, method->method);
    
    if (params_length_validate(str_params, 2) == 0) {
        printf("Parametros (%s) | São menores que o tamanho mínimo", str_params);
        return 0;
    }
    
    Param * params = get_params(str_params);
    
    if (!params) {
        printf("Parametros (%s) | Falha na coleta dos parametros", str_params);
        return 0;
    }
    
    
}

int validate_i_method(char * params, Method * method) {
    // printf("Validando método I com a instrução %s e método %s\n", params, method->method);
}

int validate_j_method(char * params, Method * method) {
    // printf("Validando método J com a instrução %s e método %s\n", params, method->method);
}

Method * construct_method(char * method, char type) {
    Method * m = malloc(sizeof(Method));
    
    if (m) {
        m->method = method;
        m->type = type;
        
        if (type == 'R') {
            m->validate_method = validate_r_method;
        } else if (type == 'I') {
            m->validate_method = validate_i_method;
        } else if (type == 'J') {
            m->validate_method = validate_j_method;
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