#include "../tools/libs.h"
#include "Label.h"

Label * construct_label(char * value, Instruction * inst);
Instruction * get_inst_on_labels(char * search_value, Label * head);
Label * create_new_label(char * value, Instruction * inst, Label * head);
char * clean_label(char * value);