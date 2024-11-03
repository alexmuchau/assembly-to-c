#include "Memory.h"

Memory * construct_memory();

Address * construct_address(char * tag, int value);
void add_address(Memory ** m, Address * a);
Address ** get_address(Memory ** m, Address * a, char * tag);