//////////////////////////////////////////////////

// Alex Muchau
// Assembly to C

//////////////////////////////////////////////////

#include "../tools/libs.h"
#include "Param.h"
#include "../Instruction/Instruction.h"

Param * construct_param(char * param, Param * before);
Param * get_head_param(Param * p);
void get_params(Instruction ** inst, char * params);