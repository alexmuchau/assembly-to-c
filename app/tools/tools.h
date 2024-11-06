#include "libs.h"
#include "../Instruction/methods.h"
#include "../Method/Method.h"
#include "../Memory/Memory.h"
#include "../Label/Label.h"

int print_header_spacer();
int print_spacer();
int init_menu();
void switch_case(int ** regs, Memory ** memory, Label ** label, Method * methods[9], int opt);
