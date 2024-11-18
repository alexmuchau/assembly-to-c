#include "libs.h"
#include "../Instruction/methods.h"
#include "../Method/Method.h"
#include "../Hardware/Memory/Memory.h"
#include "../Label/Label.h"
#include "../Hardware/RegBase/RegBase.h"

int print_header_spacer();
int print_spacer();
int init_menu();
void switch_case(RegBase * rb, Memory ** memory, Label ** label, Method * methods[11], Instruction ** head, int opt);
