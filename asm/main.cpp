#include "asm.h"

extern FILE* assembler_file;
extern int tags[10];

int main()
{
    if (assembler_file == NULL)
        printf("ASM FILE NOT OPENED!!!");
    print_all_commands(assembler_file);
    /*
    for (int i = 0 ; i < 10 ; i++)
    {
        printf("tags[%d] = %d;\n", i, tags[i]);
    }
    printf("\n");*/
    return 0;
}