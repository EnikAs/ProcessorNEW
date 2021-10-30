#include "asm.h"

extern FILE* assembler_file;
extern int tags[10];

int main()
{
    FILE* calc_file = fopen("C:/VSCprogs/Processor/quadratic.txt", "r");
    if (calc_file == NULL)
        printf("CALC FILE NOT OPENED!!!");

    FILE* assembler_file = fopen("C:/VSCprogs/Processor/assembler.jopa", "wb");
    if (assembler_file == NULL)
        printf("ASM FILE NOT OPENED!!!");

    print_all_commands(assembler_file, calc_file);
    /*
    for (int i = 0 ; i < 10 ; i++)
    {
        printf("tags[%d] = %d;\n", i, tags[i]);
    }
    printf("\n");*/
    return 0;
}