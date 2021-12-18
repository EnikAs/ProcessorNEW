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

const int TAG_MAX_CUNT = 20;

typedef int elem_t;

enum end_of_files
{
    END_OF_FILE,
    NOT_END_OF_FILE,
    INCORRECT_INPUT
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

struct asm_tag
{
    int tag_value = 0;
    int tag_hash = 0;
};

struct asm_tags
{
    asm_tag* tag;
    int free = 0;
};



size_t       scanf_file_size            (FILE* file_stream);

int          print_all_commands         (FILE* assembler_file, FILE* calc_file);

int          buffer_init                (buffer* buf, FILE* file_stream);

void         buf_string_cunt            (buffer* buf);

int          get_all_commands           (Commands* com, buffer* buf);

int          get_one_command            (Commands* com, buffer* buf);

int          push_one_command           (Commands* com, char_mas* array, int* tmp_com, asm_tags* tag);

int          tags_check                 (asm_tags* tags, int input_hash);

int          init_cmd_bait              (int num, Commands* com, char_mas* array, int* tmp_com, double* tmp_int, char* tmp_reg, char* skobka, int* tags, Cmd* bait, int* tmp_tag);

Commands*    commands_init              (buffer* buf);

int          murmurHash                 (char * key, unsigned int len);

#endif 