#ifndef METH_LIB
#define METH_LIB

struct Method;
typedef struct Method Method;

struct Method {
    char * method;
    char type;
    int (*validate_method)(char * params, Method * method);
};

#endif