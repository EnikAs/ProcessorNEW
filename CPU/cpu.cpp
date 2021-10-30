
#include "cpu.h"

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
    //free!!!!!!!!!
    cpu->data = (char*) calloc(file_size, 1);
    fread(cpu->data, sizeof(char), file_size, input_file);
    cpu->data_size = file_size;
    fclose(input_file);

    return cpu;
}

#undef DEF_CMD

#define DEF_CMD(num, name, arg, code)   \
    else if(cmd.cmd == num)             \
    {                                   \
        code                            \
    }                                   \

int do_one_command (CPU* cpu)
{
    double tmp_int = 0;
    int tmp_reg = 0;
    int tmp_ram = 0;

    Cmd cmd = {};
    cmd = *((Cmd*)(cpu->data + cpu->ip));
    cpu->ip += 1;

    //cpu_dump(cpu);
    
    if(0);

    #include "C:/VSCprogs/Processor/define.define"
    
    else
    {
        printf ("INCORRECT INPUT!!");
        return INCORRECT_INPUT;
    }
    return CORRECT;
    }

void cpu_dump(CPU *cpu)
{
	assert(cpu);
	
    int size = cpu->data_size;

	for (int i = 0; i!= size; i++) {
		printf("%02d ", i);
	}

	printf("\n");

	for (int i = 0; i != size; i++) {
		printf("%02x ", (unsigned char)cpu->data[i]);
	}

	printf("\n");
	printf("%*s\n", cpu->ip * 3 - 2, "^");

    getchar();
	//sleep(2);
}
    
int do_all_commands (FILE* input_file, CPU* cpu)
{
    StackCtor(&cpu->stk, 10);
    get_commands_from_asm(input_file, cpu); 
    int correct_check = -1;
    while (cpu->ip < cpu->data_size)
    {
        correct_check = do_one_command(cpu);
        if (correct_check == THIS_IS_SMTH_NEW_INCORRECT_INPUT)
            return THIS_IS_SMTH_NEW_INCORRECT_INPUT;
        if (correct_check == END_OF_PROG)
            return END_OF_PROG;
    }
    return CORRECT;
}
/*
    else if (command == PUSH)
    {
        if (cmd.reg == 1)
        {
            tmp_reg = *((char*)(cpu->data + cpu->ip));
            cpu->ip += 1;
            if (cmd.konst == 1)
            {
                tmp_int = *((int*)(cpu->data + cpu->ip));
                cpu->ip += 4;

                if (cmd.ram == 1)
                {
                    tmp_ram = cpu->ram[tmp_int + cpu->reg[tmp_reg]];
                    StackPush(&cpu->stk, tmp_ram);
                    return CORRECT;
                }

                StackPush(&cpu->stk, tmp_int + cpu->reg[tmp_reg]);
                return CORRECT;
            }

            else if (cmd.ram == 1)
            {
                tmp_ram = cpu->ram[cpu->reg[tmp_reg]];
                StackPush(&cpu->stk, tmp_ram);
                return CORRECT;
            }

            StackPush(&cpu->stk, cpu->reg[tmp_reg]);
            return CORRECT;
        }

        tmp_int = *((int*)(cpu->data + cpu->ip));
        cpu->ip += 4;

        if (cmd.ram == 1)
        {   
            tmp_ram = cpu->ram[tmp_int];
            StackPush(&cpu->stk, tmp_ram);

            return CORRECT;
        }
        StackPush(&cpu->stk, tmp_int);
        return CORRECT;
    }

    else if (command == POP)
    {
        if (cmd.reg == 1)
        {
            tmp_reg = *((char*)(cpu->data + cpu->ip));
            cpu->ip += 1;
            if (cmd.konst == 1)
            {
                tmp_int = *((int*)(cpu->data + cpu->ip));
                cpu->ip += 4;

                if (cmd.ram == 1)
                {
                    cpu->ram[tmp_int + cpu->reg[tmp_reg]] = StackPop(&cpu->stk);

                    return CORRECT;
                }

                return INCORRECT_INPUT;
            }

            else if (cmd.ram == 1)
            {
                cpu->ram[cpu->reg[tmp_reg]] = StackPop(&cpu->stk);
                
                return CORRECT;
            }

            cpu->reg[tmp_reg] = StackPop(&cpu->stk);    
            return CORRECT;
        }

        tmp_int = *((int*)(cpu->data + cpu->ip));
        cpu->ip += 4;

        if (cmd.ram == 1)
        {   
            cpu->ram[tmp_int] = StackPop(&cpu->stk);

            return CORRECT;
        }
        
        return INCORRECT_INPUT;
    }
    */
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