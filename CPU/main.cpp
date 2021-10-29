#include "cpu.h"

extern FILE* input_file;

int main()
{
    CPU cpu = {};
    system("C:/VSCprogs/Processor/asm/asm.exe");
    
    int corch = do_all_commands(input_file, &cpu);
    if(corch == INCORRECT_INPUT)
        assert(ERROR && "TOBI PIZDA NEXT TIME");
    for (int i = 0 ; i < REG_CUNT; i++)
    {
        printf ("%cx = %d\n", i + 'a', cpu.reg[i]);
    }
    
    for(int i = 0 ; i < 15; i++)
    {
        printf ("RAM[%d] = %d;\n", i, cpu.ram[i]);
    }
    $StackDump(&cpu.stk);

    return 0;
}