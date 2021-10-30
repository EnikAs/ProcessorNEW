#ifndef COMMSENUM_H_INCLUDED
#define COMMSENUM_H_INCLUDED

#include <cmath>
#include <windows.h>
#define DEF_CMD(num, name, ...)    \
CODE_##name = num,     

typedef double cpu_val;     

const int EPSILON = 1e-2;
enum commands
{
    #include "define.define"
};

/*
enum commands
{
    PUSH = 1,
    POP  = 2,
    MUL  = 3,
    DIV  = 4,
    SUB  = 5,
    AFF  = 6,
    OUT  = 7,
    INCORRECT_INPUT = 8,
};
*/
#endif