
#include "cpu.h"

FILE* input_file = fopen("C:/VSCprogs/Processor/assembler.jopa", "rb");

int get_file_stat (FILE* input_file)
{
    struct stat file;
    if ( fstat(fileno(input_file), &file ) == -1 )
    {
        printf("FILE READING ERROR");
        return EOF;
    }
    return file.st_size;
}

CPU* get_commands_from_asm (FILE* input_file, CPU* cpu)
{
    int file_size = get_file_stat(input_file);
    
    cpu->data = (char*) calloc(file_size, 1);
    fread(cpu->data, sizeof(char), file_size, input_file);
    cpu->data_size = file_size;
    fclose(input_file);

    return cpu;
}

#undef DEF_CMD

#define DEF_CMD(num, name, ...)         \
    case name:                          \
        return name;                    \
        break;                          \
        
int init_one_command (CPU* cpu)
{
    Cmd cmd = {};
    cmd = *((Cmd*)(cpu->data + cpu->ip));
    printf("|%u|\t|%u|\t|%u|\t|%d|\n", cmd.ram, cmd.reg, cmd.konst, cmd.cmd);
   // printf("hui->%d<-\n", (char)cmd);
    switch((int)cmd.cmd)
    {
        #include "C:/VSCprogs/Processor/define.define"
    }
}

#undef DEF_CMD

#define DEF_CMD(num, name, arg, code)   \
    else if(command == name)            \
    {                                   \
        code                            \
        buf->tmp_elem += arg;           \
    }                                   \

int do_one_command (CPU* cpu)
{
    int tmp_int = 0;
    int tmp_reg = 0;
    int command = init_one_command(cpu);

    Cmd cmd = {};
    cmd = *((Cmd*)(cpu->data + cpu->ip));
    cpu->ip += 1;
    if(0);

    //#include "C:/VSC progs/Processor/define.define"
    
    else if (command == PUSH)
    {
        printf ("I AM IN PUSH\n");
        if (cmd.reg == 1)
        {
            tmp_reg = *((char*)(cpu->data + cpu->ip));
            printf("tmp_reg ->%d<-\n", tmp_reg);
            cpu->ip += 1;
            if (cmd.konst == 1)
            {
                tmp_int = *((int*)(cpu->data + cpu->ip));
                cpu->ip += 4;

                if (cmd.ram == 1)
                {
                    cpu->ram[cpu->ram_ip] = tmp_int + cpu->reg[tmp_reg];
                    cpu->ram_ip += 1;
                    return 0;
                }

                StackPush(&cpu->stk, tmp_int + cpu->reg[tmp_reg]);
                return 0;
            }
            StackPush(&cpu->stk, cpu->reg[tmp_reg]);
            return 0;
        }
        tmp_int = *((int*)(cpu->data + cpu->ip));
        cpu->ip += 4;
        if (cmd.ram == 1)
        {   
            cpu->ram_ip += 1;
            cpu->ram[cpu->ram_ip] = tmp_int;

            return 0;
        }
        printf ("I AM GONNA PUSH!!!\n");
        StackPush(&cpu->stk, tmp_int);
        return 0;
    }

    else if (command == POP)
    {
        printf ("I AM IN POP\n");
        if (cmd.reg == 1)
        {
            tmp_reg = *((char*)(cpu->data + cpu->ip));
            printf("tmp_reg ->%d<-\n", tmp_reg);
            cpu->ip += 1;
            if (cmd.konst == 1)
            {
                tmp_int = *((int*)(cpu->data + cpu->ip));
                cpu->ip += 4;

                if (cmd.ram == 1)
                {
                    cpu->reg[tmp_reg] = tmp_int + cpu->ram[cpu->ram_ip];
                    cpu->ram[cpu->ram_ip] = 0;
                    cpu->ram_ip -= 1;
                    return 0;
                }

                cpu->reg[tmp_reg] = StackPop(&cpu->stk) + tmp_int;
                return 0;
            }
            if (cmd.ram == 1)
                {
                    cpu->reg[tmp_reg] = cpu->ram[cpu->ram_ip];
                    cpu->ram[cpu->ram_ip] = 0;
                    cpu->ram_ip -= 1;
                    assert(cpu->ram_ip >= 0);
                    return 0;
                }
            cpu->reg[tmp_reg] = StackPop(&cpu->stk);
            return 0;
        }
        tmp_int = *((int*)(cpu->data + cpu->ip));
        cpu->ip += 4;
        if (cmd.ram == 1)
        {
            return INCORRECT_INPUT;
        }
        printf ("I AM GONNA POP!!!\n");
        StackPop(&cpu->stk);
        return 0;
    }
    /*
    else if (command == MUL)
    {
        StackPush(stk, StackPop(stk) * StackPop(stk));
    }

    else if (command == DIV)
    {
        StackPush(stk, StackPop(stk) / StackPop(stk));
    }

    else if (command == SUB)
    {
        StackPush(stk, StackPop(stk) - StackPop(stk));
    }

    else if (command == AFF)
    {
        StackPush(stk, StackPop(stk) + StackPop(stk));
    }

    else if (command == OUT)
    {
        StackDtor(stk);
    }
    */
    else
    {
        printf ("INCORRECT INPUT TOBI PIZDA!!!");
        return INCORRECT_INPUT;
    }
    return CORRECT;

}

int do_all_commands (FILE* input_file, CPU* cpu)
{
    StackCtor(&cpu->stk, 10);
    get_commands_from_asm(input_file, cpu); 
    int correct_check = -1;
    while (cpu->ip < cpu->data_size)
    {
        correct_check = do_one_command(cpu);
        if (correct_check == INCORRECT_INPUT)
            return INCORRECT_INPUT;
    }
    return CORRECT;
}
