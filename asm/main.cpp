#include "asm.h"

extern FILE* assembler_file;

int main()
{
    FILE* calc_file = fopen("C:/VSCprogs/Processor/circle.txt", "r");
    if (calc_file == NULL)
        printf("CALC FILE NOT OPENED!!!");

    FILE* assembler_file = fopen("C:/VSCprogs/Processor/assembler.jopa", "wb");
    if (assembler_file == NULL)
        printf("ASM FILE NOT OPENED!!!");

    print_all_commands(assembler_file, calc_file);
    
    return 0;
}