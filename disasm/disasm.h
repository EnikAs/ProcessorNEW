
#ifndef DISASM_H_INCLUDED
#define DISASM_H_INCLUDED

#include <iostream>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cassert>
#include <sys\stat.h>


#include "C:/VSCprogs/Processor/cmd-enum.h"

struct com_buff
{
    cpu_val* data;
    int tmp_elem = 0;
    int com_cunt = 0;
};

int get_file_stat (FILE* input_file);

com_buff* get_commands_from_asm (FILE* input_file);

int dis_one_command (com_buff* buf);

int dis_all_commands (FILE* input_file);

int init_one_command (com_buff* buf);

#endif 
