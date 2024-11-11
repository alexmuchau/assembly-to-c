#include "../tools/libs.h"
#include "Instruction.h"

#include "../Method/methods.h"
#include "../Param/Param.h"
#include "../Memory/Memory.h"
#include "../Label/methods.h"

Instruction * construct_inst(Instruction *before);
Instruction * inst_reader(int init_address);
int validate_instruction(Instruction ** inst, Label ** label, Method * methods[11]);
Instruction * execute_instructions(Instruction ** inst, int ** regs, Memory ** memory, Label ** label);

Instruction * find_inst_front(int address_to_search, Instruction * inst);
Instruction * find_inst_back(int address_to_search, Instruction * inst);