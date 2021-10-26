#include "asm.h"

extern FILE* assembler_file;

int main()
{
    if (assembler_file == NULL)
        printf("Govno");
    print_all_commands(assembler_file);
    printf("YEES");
    return 0;
}