#include "cpu.h"

extern FILE* input_file;

int main()
{
    CPU cpu = {};
    
    system("C:/VSCprogs/Processor/asm/asm.exe");
    
    int corcheck = do_all_commands(input_file, &cpu);
    if(corcheck == INCORRECT_INPUT)
        assert(ERROR && "INCORRECT INPUT? OK, CHECK YOUR <C> DRIVE");
    /*
    for (int i = 0 ; i < REG_CUNT; i++)
    {
        printf ("%cx = %d\n", i + 'a', cpu.reg[i]);
    }
    
    for(int i = 0 ; i < 15; i++)
    {
        printf ("RAM[%d] = %d;\n", i, cpu.ram[i]);
    }
    */
    $StackDump(&cpu.stk);

    return 0;
}