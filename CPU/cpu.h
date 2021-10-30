#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#include <iostream>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cassert>
#include <sys\stat.h>
#include <unistd.h>

#include "stackfunc.h"
#include "C:/VSCprogs/Processor/cmd-enum.h"

#define SETIP                                       \
tmp_int = *((cpu_val*)(cpu->data + cpu->ip));       \
cpu->ip = (int)tmp_int;                             \

#define $PUSH(arg) StackPush(&cpu->stk, arg)
#define $POP StackPop(&cpu->stk)

const int RAM_SIZE = 10000;
const int VRAM_SIZE = 2500;
const int REG_CUNT = 6;

enum for_end
{
    END_OF_PROG = 1488,
    INCORRECT_INPUT
};
struct CPU 
{
    Stack stk = {};
    char* data;
    int ip = 0;
    int data_size = 0;

    double reg[REG_CUNT] = {};
    /* 
    вот они слева направо 
    ax  =   reg[0]; 
    bx  =   reg[1];
    cx  =   reg[2];
    dx  =   reg[3];
    ex  =   reg[4];
    fx  =   reg[5];
    */
    double ram[RAM_SIZE + VRAM_SIZE] = {};
    int ram_ip = 0;
};

struct Cmd
{
    unsigned ram : 1;
    unsigned reg : 1;
    unsigned konst : 1;
    unsigned cmd : 5;
};

void cpu_dump(CPU *cpu);

int get_file_stat (FILE* input_file);

CPU* get_commands_from_asm (FILE* input_file, CPU* buf);

int do_one_command (CPU* cpu);

int do_all_commands (FILE* input_file, CPU* cpu);

#endif 
