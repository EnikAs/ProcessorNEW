#include "cpu.h"


int main()
{
    CPU cpu = {};
    FILE* input_file = fopen("C:/VSCprogs/Processor/assembler.jopa", "rb");

    system("C:/VSCprogs/Processor/asm/asm.exe");

    int corcheck = do_all_commands(input_file, &cpu);
    if(corcheck == CODE_INCORRECT_INPUT)
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
    //$StackDump(&cpu.stk);//НЕЛЬЗЯ ДРОПАТЬ ПРОГУ ПРИ ДАМПЕ
    //КВАДРАТКУ ФИКСИТЬ 

    return 0;
}