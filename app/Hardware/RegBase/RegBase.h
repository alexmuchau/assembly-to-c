//////////////////////////////////////////////////

// Alex Muchau
// Assembly to C

//////////////////////////////////////////////////

#ifndef REG_LIB
#define REG_LIB

struct RegBase;
typedef struct RegBase RegBase;

struct RegBase {
    int regs[32];
    
    int (* get_reg_value)(int reg, int regs[32]);
    int (* write_back)(int reg, int value, int (*regs)[32]);
};

#endif