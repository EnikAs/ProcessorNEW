#include "asm.h"

FILE* calc_file = fopen("C:/VSCprogs/Processor/calc.txt", "r");
FILE* assembler_file = fopen("C:/VSCprogs/Processor/assembler.jopa", "wb");

int print_all_commands (FILE* file_stream)
{
    if (assembler_file == NULL)
        printf("NULL!!!");

    buffer* buf = (buffer*) calloc(1, sizeof(buffer));
    
    char_mas array = {};
    
    //Stack proc_stack = {};
    //StackCtor(&proc_stack, 7);
    //char code[1000] = {};// TODO calloc на sizeof(typdef)*2*колличество строк

    buffer_init(buf, calc_file);
    
    Commands* com = commands_init(buf);
    
    get_all_commands(com, buf);
    

    for (int i = 0 ; i < buf->buffer_size ; i++)
    {
        if (buf->buffer[i] == ';' && buf->buffer[i])
        {
            buf->buffer[i] = '\0';
        }
    }
    
    //StackPush(&proc_stack, buf->words_cunt);

    int tmp_com = 0;
    
    for (tmp_com = 0 ; tmp_com < buf->tmp_string_cunt ; tmp_com++)
    {
        push_one_command(com, &array, &tmp_com);
    }
    
    fwrite(array.mas, sizeof(char), array.ip , assembler_file); // +1 не нужно, так как ip сам увеличивается на эту "дополнительную" единицу 
    
    fclose(calc_file);
    fclose(assembler_file);
    free(com);
    free(buf->buffer);

    return 0;
}

size_t scanf_file_size (FILE* input_file)
{
    struct stat file;
    if ( fstat(fileno(input_file), &file ) == -1 )
    {
        printf("FILE READING ERROR");
        return EOF;
    }

    //printf("govno %d govno\n", file.st_size);
    return file.st_size;
}


int buffer_init (buffer* buf, FILE* file_stream)
{
    
    buf->buffer_size = scanf_file_size (file_stream);
    
    buf->buffer = (char*) calloc(buf->buffer_size, sizeof(char));
    
    if (buf->buffer == NULL)
    {
        printf("buf->buffer == NULL\n");
    }
    
    //printf("hui %d hui", buf->buffer_size);
    buf->buffer_size = fread(buf->buffer, sizeof(char), buf->buffer_size, file_stream);
    
    //printf("123%s123", buf->buffer);
    buf_string_cunt(buf);
    
    return 0;
}

void buf_string_cunt (buffer* buf)
{
    size_t string_cunt = 0;
    for (int i = 0 ; i < buf->buffer_size ; i++)
    {
        if (buf->buffer[i] == '\n' || buf->buffer[i] == ' ')
        {
            
            if(buf->buffer[i] == '\n')
                buf->string_cunt += 1;

            buf->buffer[i] = '\0';
            buf->words_cunt += 1;      
        }
    }
    buf->words_cunt += 1; 

}

Commands* commands_init (buffer* buf)
{
    Commands* com = (Commands*) calloc(buf->words_cunt + 1, sizeof(Commands));// СТАЛО
    if (com == NULL)
    {   
        printf("NOT ENOUGH MEMORY");
        return NULL;
    }
    return com;
}

int get_all_commands (Commands* com, buffer* buf)
{
    int end_check = -1;
    
    while (end_check != END_OF_FILE)
    {
        end_check = get_one_command(com, buf);
    }

    return 0;
}

int get_one_command (Commands* com, buffer* buf)
{
    
    //printf("%d\n", buf->tmp_string_cunt);
    //printf("%s", buf->buffer);
    
    com[buf->tmp_string_cunt].command = ((char*)buf->buffer + buf->tmp_pos);
    //printf("|%s|\n", com[buf->tmp_string_cunt].command);
    com[buf->tmp_string_cunt].lenght = strlen(com[buf->tmp_string_cunt].command);
    //printf("->%d<-\n", com[buf->tmp_string_cunt].lenght);
    if (com[buf->tmp_string_cunt].lenght > 0)
    {
        //printf("|%s|\n", com[buf->tmp_string_cunt].command);
        buf->tmp_string_cunt++;
    }
    
    
    while (buf->buffer[buf->tmp_pos] != '\0')
    {
        buf->tmp_pos++;
    } 

    buf->tmp_pos++;
    
    if (buf->tmp_pos > buf->buffer_size)
    {
        
        return END_OF_FILE;
    }
    return -1;
}


#undef DEF_CMD

#define DEF_CMD(num, name, arg, ...)                                                           \
else if (strcmp(com[*tmp_com].command, #name) == 0)                                            \
    {                                                                                          \
        if (arg > 0)                                                                           \
        {                                                                                      \
            *tmp_com += 1;                                                                     \
            if (sscanf(com[*tmp_com].command, "[%d+%cx%c", &tmp_int, &tmp_reg, &skobka) == 3)  \
            {                                                                                  \
                if (skobka == ']')                                                             \
                {                                                                              \
                bait.ram = 1;                                                                  \
                bait.reg = 1;                                                                  \
                bait.konst = 1;                                                                \
                bait.cmd = name;                                                               \
                }                                                                              \
                else                                                                           \
                    return INCORRECT_INPUT;                                                    \
                *((Cmd*)((char*)array->mas + array->ip)) = bait;                               \
                array->ip += 1;                                                                \
                *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';                     \
                array->ip += 1;                                                                \
                *((int*)((char*)array->mas + array->ip)) = tmp_int;                            \
                array->ip += 4;                                                                \
            }                                                                                  \
            else if (sscanf(com[*tmp_com].command, "[%cx%c", &tmp_reg, &skobka) == 2)          \
            {                                                                                  \
                printf("povezlo");if (skobka == ']')                                                             \
                {printf("povezlo");                                                                              \
                bait.ram = 1;                                                                  \
                bait.reg = 1;                                                                  \
                bait.cmd = name;                                                               \
                }                                                                              \
                else                                                                           \
                    return INCORRECT_INPUT;                                                    \
                *((Cmd*)((char*)array->mas + array->ip)) = bait;                               \
                array->ip += 1;                                                                \
                *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';                     \
                array->ip += 1;                                                                \
            }                                                                                  \
            else if (sscanf(com[*tmp_com].command, "[%d%c", &tmp_int, &skobka) == 2)           \
            {                                                                                  \
                if (skobka == ']')                                                             \
                {                                                                              \
                bait.ram = 1;                                                                  \
                bait.konst = 1;                                                                \
                bait.cmd = name;                                                               \
                }                                                                              \
                else                                                                           \
                    return INCORRECT_INPUT;                                                    \
                *((Cmd*)(array->mas + array->ip)) = bait;                                      \
                array->ip += 1;                                                                \
                *((int*)(array->mas + array->ip)) = tmp_int;                                   \
                array->ip += 4;                                                                \
            }                                                                                  \
            else if (sscanf(com[*tmp_com].command, "%cx", &tmp_reg) == 1 && isalpha(tmp_reg) != 0)  \
            {                                                                                  \
                bait.reg = 1;                                                                  \
                bait.cmd = name;                                                               \
                *((Cmd*)(array->mas + array->ip)) = bait;                                      \
                array->ip += 1;                                                                \
                *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';                     \
                array->ip += 1;                                                                \
            }                                                                                  \
            else if(sscanf(com[*tmp_com].command, "%d", &tmp_int) == 1)                        \
            {                                                                                  \
                bait.konst = 1;                                                                \
                bait.cmd = name;                                                               \
                *((Cmd*)(array->mas + array->ip)) = bait;                                      \
                array->ip += 1;                                                                \
                *((int*)(array->mas + array->ip)) = tmp_int;                                   \
                array->ip += 4;                                                                \
            }                                                                                  \
        }                                                                                      \
        else                                                                                   \
        {                                                                                      \
            bait.cmd = name;                                                                   \
            *((Cmd*)(array->mas + array->ip)) = bait;                                          \
            array->ip += 1;                                                                    \
        }                                                                                      \
    }                                                                                          \

int push_one_command (Commands* com, char_mas* array, int* tmp_com)
{
    Cmd bait = {};
    int tmp_int = 0; 
    char tmp_reg = 0;
    char skobka = 0;
    //printf("--%s--\n", com[*tmp_com].command);
    if (strlen(com[*tmp_com].command) == 0)
        return 0;

    #include "C:/VSCprogs/Processor/define.define"

    else
    {  
        printf("INCORRECT!!!\n");
        bait.cmd = INCORRECT_INPUT;    
        *((Cmd*)(array->mas + array->ip)) = bait;
        array->ip += 1; // sizeof(bait)
    }
    return 0;
}
/*
    else if (strcmp(com[*tmp_com].command, "PUSH") == 0)
    {
        
        *tmp_com += 1;
        if (sscanf(com[*tmp_com].command, "[%d+%cx%c", &tmp_int, &tmp_reg, &skobka) == 3) // ввод в ОП с регистром, команда вида push [123+ax]
        {
            
            if (skobka == ']')
            {
            bait.ram = 1;
            bait.reg = 1;
            bait.konst = 1;
            bait.cmd = PUSH;
            }
            else 
                return INCORRECT_INPUT;
                
            *((Cmd*)((char*)array->mas + array->ip)) = bait;
            array->ip += 1; // sizeof(bait)
            *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';
            array->ip += 1; // sizeof(tmp_reg)
            *((int*)((char*)array->mas + array->ip)) = tmp_int;
            array->ip += 4;
        }
        else if (sscanf(com[*tmp_com].command, "[%cx%c", &tmp_reg, &skobka) == 2) // команда вида push [ax]
        {
            
            if (skobka == ']')
            {
            bait.ram = 1;
            bait.reg = 1;
            bait.cmd = PUSH;
            }
            else 
                return INCORRECT_INPUT;

            *((Cmd*)(char*)array->mas + array->ip) = bait;
            array->ip += 1; // sizeof(bait)
            *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';
            array->ip += 1; // sizeof(tmp_reg)
        }    
        else if (sscanf(com[*tmp_com].command, "[%d%c", &tmp_int, &skobka) == 2) // команда вида push [123]
        {
            
            if (skobka == ']')
            {
            bait.ram = 1;
            bait.konst = 1;
            bait.cmd = PUSH;
            }
            else 
                return INCORRECT_INPUT;

            *((Cmd*)(array->mas + array->ip)) = bait;
            array->ip += 1; // sizeof(bait)
            *((int*)(array->mas + array->ip)) = tmp_int;
            array->ip += 4;
        }  
        else if (sscanf(com[*tmp_com].command, "%cx", &tmp_reg) == 1 && isalpha(tmp_reg) != 0) // просто регистр, команда вида push ax
        {
            
            bait.reg = 1;
            bait.cmd = PUSH;

            *((Cmd*)(array->mas + array->ip)) = bait;
            array->ip += 1; // sizeof(bait)
            *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';
            array->ip += 1; // sizeof(tmp_reg)
        }   
        else if(sscanf(com[*tmp_com].command, "%d", &tmp_int) == 1)// команда вида push 123
        {
            
            bait.konst = 1;
            bait.cmd = PUSH;

            printf("int = %d\n", tmp_int);
            *((Cmd*)(array->mas + array->ip)) = bait;
            array->ip += 1; // sizeof(bait)
            *((int*)(array->mas + array->ip)) = tmp_int;
            array->ip += 4;
        }
    }
    else if (strcmp(com[*tmp_com].command, "POP") == 0)// начало POP ----------------------------------------------------------------------------------------------------------------
    {
        
        *tmp_com += 1;
        if (sscanf(com[*tmp_com].command, "[%d+%cx%c", &tmp_int, &tmp_reg, &skobka) == 3) // ввод в ОП с регистром, команда вида push [123+ax]
        {
            if (skobka == ']')
            {
            bait.ram = 1;
            bait.reg = 1;
            bait.konst = 1;
            bait.cmd = POP;
            }
            else 
                return INCORRECT_INPUT;
                
            *((Cmd*)(array->mas + array->ip)) = bait;
            array->ip += 1; // sizeof(bait)
            *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';
            array->ip += 1; // sizeof(tmp_reg)
            *((int*)((char*)array->mas + array->ip)) = tmp_int;
            array->ip += 4;
        }
        else if (sscanf(com[*tmp_com].command, "[%cx%c", &tmp_reg, &skobka) == 2) // команда вида push [ax]
        {
            if (skobka == ']')
            {
            bait.ram = 1;
            bait.reg = 1;
            bait.cmd = POP;
            }
            else 
                return INCORRECT_INPUT;

            *((Cmd*)(array->mas + array->ip)) = bait;
            array->ip += 1; // sizeof(bait)
            *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';
            array->ip += 1; // sizeof(tmp_reg)
        }    
        else if (sscanf(com[*tmp_com].command, "[%d%c", &tmp_int, &skobka) == 2) // команда вида push [123]
        {
            if (skobka == ']')
            {
            bait.ram = 1;
            bait.konst = 1;
            bait.cmd = POP;
            }
            else 
                return INCORRECT_INPUT;

            *((Cmd*)(array->mas + array->ip)) = bait; 
            array->ip += 1; // sizeof(bait)
            *((int*)((char*)array->mas + array->ip)) = tmp_int;
            array->ip += 4;
        }  
        else if (sscanf(com[*tmp_com].command, "%cx", &tmp_reg) == 1) // просто регистр, команда вида push ax
        {
            bait.reg = 1;
            bait.cmd = POP;

            *((Cmd*)(array->mas + array->ip)) = bait;
            array->ip += 1; // sizeof(bait)
            *((char*)((char*)array->mas + array->ip)) = tmp_reg - 'a';
            array->ip += 1; // sizeof(tmp_reg)
        }   
        else if(sscanf(com[*tmp_com].command, "%d", &tmp_int) == 1)// команда вида push 123
        {
            bait.konst = 1;
            bait.cmd = POP;

            *((Cmd*)(array->mas + array->ip)) = bait;// правильная запись 
            array->ip += 1; // sizeof(bait)
            *((int*)((char*)array->mas + array->ip)) = tmp_int; // тоже правильная запись
            array->ip += 4;
        }
    }

    else if (strcmp(com[*tmp_com].command, "MUL") == 0)
    {
        bait.cmd = MUL;
        *((Cmd*)(array->mas + array->ip)) = bait;
        array->ip += 1; // sizeof(bait)
    }

    else if (strcmp(com[*tmp_com].command, "SUB") == 0)
    {
        bait.cmd = SUB;
        *((Cmd*)(array->mas + array->ip)) = bait;
        array->ip += 1; // sizeof(bait)
    }

    else if (strcmp(com[*tmp_com].command, "DIV") == 0)
    {
        bait.cmd = DIV;    
        *((Cmd*)(array->mas + array->ip)) = bait;
        array->ip += 1; // sizeof(bait)
    }

    else if (strcmp(com[*tmp_com].command, "OUT") == 0)
    {
        bait.cmd = OUT;    
        *((Cmd*)(array->mas + array->ip)) = bait;
        array->ip += 1; // sizeof(bait)
    }

    else if (strcmp(com[*tmp_com].command, "AFF") == 0)
    {
        bait.cmd = AFF;    
        *((Cmd*)(array->mas + array->ip)) = bait;
        array->ip += 1; // sizeof(bait)
    }
    */