#include "../tools/libs.h"
#include "Instruction.h"

#include "../Method/methods.h"
#include "../Param/Param.h"

Instruction * inst_reader();
int get_and_validate_instructions(Instruction ** instruction, Method * methods[9]);
void execute_instruction(Instruction * inst, int ** regs);
