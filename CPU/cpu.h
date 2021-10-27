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

#include "stackfunc.h"
//#include "C:/VSC progs/Processor/stackfunc.cpp"
#include "C:/VSCprogs/Processor/cmd-enum.h"

const int RAM_SIZE = 10000;
const int VRAM_SIZE = 10000;
const int REG_CUNT = 4;

struct CPU 
{
    Stack stk = {};
    char* data;
    int ip = 0;
    int data_size = 0;

    int reg[REG_CUNT] = {};
    /* 
    вот они слева направо 
    ax  =   reg[0]; 
    bx  =   reg[1];
    cx  =   reg[2];
    dx  =   reg[3];
    */
    int ram[RAM_SIZE + VRAM_SIZE] = {};
    int ram_ip = 0;
};

struct Cmd
{
    unsigned ram : 1;
    unsigned reg : 1;
    unsigned konst : 1;
    unsigned cmd : 5;
};

int get_file_stat (FILE* input_file);

CPU* get_commands_from_asm (FILE* input_file, CPU* buf);

int do_one_command (CPU* cpu);

int init_one_command (CPU* cpu);

int do_all_commands (FILE* input_file, CPU* cpu);

#endif 
