#ifndef LAB_M_LIB
#define LAB_M_LIB

#include "methods.h"

Label * find_label(char * search_value, Label * head) {
    if (!head) return NULL;
    
    if (strcmp(search_value, head->value) == 0) return head;
    
    if (!head->next) return head;
    return find_label(search_value, head->next);
}

Label * construct_label(char * value, Instruction * inst) {
    Label * l = malloc(sizeof(Label));
    l->value = value;
    l->inst = inst;
    l->next = NULL;
    
    return l;
}

char * clean_label(char * value) {
    int total_len = strlen(value), left_trim = 0, right_trim = 0;
    
    // left trim
    while (isspace(value[left_trim]) && value[left_trim] != '\0') left_trim++;
    
    // apenas espaço
    if (left_trim == total_len) return NULL;
    
    // right trim
    while (isspace(value[total_len - right_trim])) right_trim++;
    
    total_len -= right_trim;
    
    // caso de não ter os 2 pontos após o label
    if (value[total_len - right_trim - 1] == ':') {
        total_len -= 1;
    }
    
    char * result = malloc(sizeof(char)*(total_len - left_trim));
    for (int i = left_trim ; i < total_len; i++) {
        result[i - left_trim] = value[i];
    }
    
    return result;
}

Instruction * get_inst_on_labels(char * search_value, Label * head) {
    Label * l = find_label(search_value, head);
    if (!l) return NULL;
    
    char * clean_value = clean_label(search_value);
    
    // printf("cv:%s == l:%s\n", clean_value, l->value);
    
    if (strcmp(clean_value, l->value) != 0) return NULL;
    
    return l->inst;
}

Label * create_new_label(char * value, Instruction * inst, Label * head) {    
    if (!head) {
        // printf("Criando novo LABEL | %s\n", value);
        return construct_label(value, inst);
    }
    
    if (strcmp(value, head->value) == 0) {
        return head;
    }
    
    head->next = create_new_label(value, inst, head->next);
    return head;
}

#endif