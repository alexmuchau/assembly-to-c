#include "../../tools/libs.h"
#include "Memory.h"

Memory * construct_memory();

Address * construct_address(int tag, int value);
void add_address(Memory ** m, Address * a);
Address * get_address(Memory ** m, Address * a, int tag);