#ifndef LAB_M_LIB
#define LAB_M_LIB

#include "methods.h"

Label * construct_label(char * value, Instruction * inst) {
    Label * l = malloc(sizeof(Label));
    l->value = value;
    l->inst = inst;
    l->next = NULL;
    
    return l;
}

Instruction * get_inst_on_labels(char * search_value, Label * head) {
    Label * l = find_label(search_value, head);
    
    if (strcmp(search_value, l->value) != 0) return NULL;
    
    return l->inst;
}

Label * find_label(char * search_value, Label * head) {
    if (strcmp(search_value, head->value) == 0) return head;
    
    if (!head->next) return head;
    return find_label(search_value, head->next);
}

void create_new_label(char * value, Instruction * inst, Label * head) {
    Label * l = construct_label(value, inst);
    
    if (strcmp(value, l->value) != 0) {
        l->next = construct_label(value, inst);
        return;
    }
}

#endif