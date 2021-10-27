#include "cpu.h"

extern FILE* input_file;

int main()
{
    CPU cpu = {};
    system("C:/VSCprogs/Processor/asm/asm.exe");
    
    do_all_commands(input_file, &cpu);

    printf ("reg = %d\n", cpu.reg[0]);
    printf ("RAM = %d, pam ip = %d\n", cpu.ram[1], cpu.ram_ip);
    $StackDump(&cpu.stk);

    return 0;
}