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
#include "cmd-enum.h"

struct com_buff
{
    elem_t* data;
    int tmp_elem = 0;
    int com_cunt = 0;
};

int get_file_stat (FILE* input_file);

com_buff* get_commands_from_asm (FILE* inputt_file, com_buff* buf);

int do_one_command (com_buff* buf, Stack* stk);

int init_one_command (com_buff* buf);

int do_all_commands (FILE* input_file, Stack* stk);

#endif 
