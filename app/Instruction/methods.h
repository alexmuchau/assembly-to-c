#include "../tools/libs.h"
#include "Instruction.h"
#include "../Method/Method.h"

Instruction * inst_reader();
int validate_instructions(Instruction * instruction, char methods[9][5]);
