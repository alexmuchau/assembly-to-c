#include "../tools/libs.h"
#include "Instruction.h"
#include "../Method/methods.h"

Instruction * inst_reader();
int validate_instructions(Instruction * instruction, Method * methods[9]);
