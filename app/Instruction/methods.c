#ifndef INST_M_LIB
#define INST_M_LIB

#include "methods.h"

int verify_line(char ** line) {
    int length = strlen(*(line));
    if (!line || length < 2) return -1;
    
    if ((*line)[length - 2] == '|') return 1;
    
    return 0;
}

Instruction * construct_inst(Instruction * before) {
    Instruction * inst = malloc(sizeof(Instruction));
    
    inst->word = NULL;
    inst->next = NULL;
    
    inst->before = before;
    if (before) before->next = inst;
    
    inst->params = NULL;
    inst->params_qtd = 0;
    
    return inst;
}

Instruction * find_head(Instruction * i) {
    if (!i) return NULL;
    if (!(i->before)) return i;
    
    return find_head(i->before);
}

Instruction * inst_reader(int init_address) {
    printf("\n\nDIGITE SEU CÓDIGO ASSEMBLY. (o último caractere deve ser um '|')\n\n");
    
    Instruction * actual_inst = NULL;
    size_t len = 0;
    size_t read;
    
    int need_to_finish = 0;
    
    while (need_to_finish < 1) {
        char * line = malloc(sizeof(char)*32);
        while ((read = getline(&line, &len, stdin)) != -1) {
            if (read > 0) {
                if (abs(need_to_finish = verify_line(&(line))) == 1) break;
                
                char * word = malloc(sizeof(char)*strlen(line));
                strcpy(word, line);
                
                actual_inst = construct_inst(actual_inst);
                // printf("Construiu -> %s\n", word);
                
                actual_inst->word = word;
                actual_inst->next = NULL;
                actual_inst->address = init_address = init_address + 4;
                
                break;
            }
        }
    }
    
    return find_head(actual_inst);
}

int lexical_verification(Instruction ** inst, char * word, Method * methods[11]) {
    int total_length = 0;
    int len = 0;
    
    // EXTRACTING METHOD
    len = 0;
    while (!isspace(word[len]) && word[len] != '\0') {len++; total_length++;}
    
    if (len == 0) return 0;
    
    char * first_arg = malloc(sizeof(char)*len);
    strncpy(first_arg, word, len);
    
    (*inst)->method = find_method(first_arg, methods);
    
    if (!(*inst)->method) {
        if (first_arg[len - 1] == ':') return 1;
        
        return 0;
    }
    
    word += len;
    len = 0;
    while (isspace(word[len]) && word[len] != '\0') len++;
    
    get_params(&(*inst), word);
    
    return 1;
}

char * trim_word(char * word) {
    int length = strlen(word);
    
    // left trim
    while (isspace(word[0]) && word[0] != '\0') word++;
    int char_qtd = strlen(word);
    
    while(isspace(word[char_qtd])) char_qtd--;
    
    char * trimmed_word = malloc(sizeof(char)*char_qtd);
    strncpy(trimmed_word, word, char_qtd);
    
    return trimmed_word;
}

int validate_instruction(Instruction ** inst, Label ** label, Method * methods[11]) {    
    if (!inst) return 0;
    
    char * cleaned_word;
    
    // printf("<Trim Word> | %s\n", (*inst)->word);
    if (!(cleaned_word = trim_word((*inst)->word))) {
        printf("Erro na remoção dos espaços | %s", (*inst)->word);
        return 0;
    }
    
    printf("<Verificação lexica> | %s\n", cleaned_word);
    if (lexical_verification(inst, cleaned_word, methods) == 0) {
        printf("Erro na verificação léxica da instrução | %s\n", cleaned_word);
        return 0;
    }
    
    // Caso seja LABEL
    if (!(*inst)->method) {
        printf("<Adicionando Label ao banco de Labels> | %s\n", cleaned_word);
        
        char * label_value = clean_label(cleaned_word);
        if (label_value) create_new_label(label_value, (*inst), (*label));
        
        // printf("\n\n");
        if (!(*inst)->next) return 1;
        return validate_instruction(&((*inst)->next), label, methods);
    }
    
    printf("<Verificação semantica> | %s\n", cleaned_word);
    if ((*inst)->method->semantical_verification((*inst)) == 0) {
        printf("Erro na verificação semântica da instrução | %s\n", cleaned_word);
        return 0;
    }
    
    if (!(*inst)->next) return 1;
    return validate_instruction(&((*inst)->next), label, methods);
}

Instruction * execute_instructions(Instruction ** inst, RegBase * rb, Memory ** memory, Label ** label) {
    if (!inst) return NULL;
    
    Instruction * next_inst;
    if ((*inst)->method) {
        next_inst = (*inst)->method->execute(inst, rb, memory, label);
    } else {
        next_inst = (*inst)->next;
    }
    
    if (next_inst) add_sp(next_inst->address, rb);
    if (!next_inst) return (*inst);
    execute_instructions(&(next_inst), rb, memory, label);
}

Instruction * find_inst_front(int address_to_search, Instruction * inst){
    if (!inst) return NULL;
    
    if (address_to_search == inst->address) return inst;
    
    return find_inst_front(address_to_search, inst->next);
}

Instruction * find_inst_back(int address_to_search, Instruction * inst){
    if (!inst) return NULL;
    
    if (address_to_search == inst->address) return inst;
    
    return find_inst_back(address_to_search, inst->before);
}

void print_code(Instruction * inst) {
    if (!inst) return;
    
    printf("%s\n", inst->word);
    print_code(inst->next);
}

#endif
