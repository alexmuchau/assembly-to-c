#include "../tools/libs.h"
#include "Instruction.h"

#include "../Method/methods.h"
#include "../Param/Param.h"
#include "../Memory/Memory.h"
#include "../Label/methods.h"

Instruction * construct_inst();
Instruction * inst_reader();
int validate_instruction(Instruction ** inst, Label ** label, Method * methods[9]);
Instruction * execute_instructions(Instruction ** inst, int ** regs, Memory ** memory, Label ** label);
