#ifndef ASM_H_INCLUDED
#define ASM_H_INCLUDED

#include <iostream>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cassert>
#include <sys\stat.h>


#include "C:/VSCprogs/Processor/cmd-enum.h"


typedef int elem_t;

enum end_of_file
{
    END_OF_FILE,
    NOT_END_OF_FILE
};

struct Commands
{
    char* command;
    int lenght;
};

struct char_mas
{
    char mas[1000] = {};
    int ip = 0;
};

struct Cmd
{
    unsigned ram : 1;
    unsigned reg : 1;
    unsigned konst : 1;
    unsigned cmd : 5;
};

struct buffer 
{
    char* buffer;
    int string_cunt = 0;
    int words_cunt = 0;
    int tmp_string_cunt = 0;
    int buffer_size = 0;
    int tmp_pos = 0;
};

size_t       scanf_file_size            (FILE* file_stream);

int          print_all_commands         (FILE* file_stream);

int          buffer_init                (buffer* buf, FILE* file_stream);

void         buf_string_cunt            (buffer* buf);

int          get_all_commands           (Commands* com, buffer* buf);

int          get_one_command            (Commands* com, buffer* buf);

int          push_one_command           (Commands* com, char_mas* array, int* tmp_com);

Commands*    commands_init              (buffer* buf);

#endif 