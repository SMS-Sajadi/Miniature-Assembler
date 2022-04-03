#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define R_type 1
#define I_type 2
#define J_type 3

const char* inst[] = {"add","sub","slt","or","nand","addi","slti","ori","lui","lw","sw","beq","jalr","j","halt"};

struct instruction
{
    int type;
    int int_of_inst;
    int opcode;
    char mnemonic[5];
    int rd;
    int rs;
    int rt;
    int imm;
    int ins_count;
};

struct symbolTable
{
    int value;
    char* symbol;
};

int findsymtab_len(FILE* inputfile)
{
    int count = 0;
    size_t line_size;
    char* line = (char*)malloc(72);
    while (fgets(line, 72, inputfile))
    {
        if (line[0] == ' ' || line[0] == '\t');
        else count++;
    }
    /*while (getline(&line, &line_size, inputfile) != -1) {}*/
    rewind(inputfile);
    free(line);
    return count;
}

void fillsymTab(symbolTable* symtab, FILE* inputfile)
{
    int nofline = 0, i = 0;
    size_t line_size;
    char* line = (char*)malloc(72);
    char* tok;
    while (fgets(line, 72, inputfile))
    {
        if (!(line[0] == ' ' || line[0] == '\t'))
        {
            tok = strtok(line, " \t ");
            strcpy(symtab[i].symbol, tok);
            symtab[i].value = nofline;
            i++;
        }
        nofline++;
    }
    rewind(inputfile);
    free(line);
}

void print_symbol(struct symbolTable* table, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s --- %d\n", table[i].symbol, table[i].value);
    }
}

void Rtomachine(struct instruction* ins)
{
    int bin_num = 0x0ffff000;
    int help = 0xfff0fff;
    int temp = ins->rd;
    temp <<= 12;
    temp |= help;
    bin_num &= temp;
    help = 0xfff0ffff;
    temp = ins->rt;
    temp <<= 16;
    temp |= help;
    bin_num &= temp;
    help = 0xff0fffff;
    temp = ins->rs;
    temp <<= 20;
    temp |= help;
    bin_num &= temp;
    help = 0xf0ffffff;
    temp = ins->opcode;
    temp <<= 24;
    temp |= help;
    bin_num &= temp;
    ins->int_of_inst = bin_num;
}

void Itomachine(struct instruction* ins)
{
    int bin_num = 0x0fffffff;
    int help = 0xffff0000;
    int temp = ins->imm;
    temp |= help;
    bin_num &= temp;
    help = 0xfff0ffff;
    temp = ins->rt;
    temp <<= 16;
    temp |= help;
    bin_num &= temp;
    help = 0xff0fffff;
    temp = ins->rs;
    temp <<= 20;
    temp |= help;
    bin_num &= temp;
    help = 0xf0ffffff;
    temp = ins->opcode;
    temp <<= 24;
    temp |= help;
    bin_num &= temp;
    ins->int_of_inst = bin_num;
}

int main(int argc, char** argv) {
    FILE* assp, * machp, * fopen();
    if (argc < 3) {
        printf("***** Please run this program as follows:\n");
        printf("***** %s assprog.as machprog.m\n", argv[0]);
        printf("***** where assprog.as is your assembly program\n");
        printf("***** and machprog.m will be your machine code.\n");
        exit(1);
    }
    if ((assp = fopen(argv[1], "r")) == NULL) {
        printf("%s cannot be openned\n", argv[1]);
        exit(1);
    }
    if ((machp = fopen(argv[2], "w+")) == NULL) {
        printf("%s cannot be openned\n", argv[2]);
        exit(1);
    }
    // here you can place your code for the assembler



    int symtab_len = findsymtab_len(assp);
    symbolTable* table = (symbolTable*)malloc(symtab_len * sizeof(symbolTable));
    for (int i = 0; i < symtab_len; i++) table[i].symbol = (char*)malloc(10);
    fillsymTab(table, assp);
   // print_symbol(table, symtab_len);

    char* line = (char*)malloc(72);
    char* tok;
    int ins_count = 0;
    struct instruction current_ins;
    while (fgets(line, 72, assp))
    {
        current_ins.ins_count = ins_count;
        ins_count++;
        if (line[0] == ' ' || line[0] == '\t')
        {
            tok = strtok(line, "\t, \n");
            strcpy(current_ins.mnemonic, tok);
            int i;
            for (i = 0; i < 15; i++)
            {
                if (strcmp(tok, inst[i]) == 0)
                {
                    current_ins.opcode = i;
                    if (i < 5) current_ins.type = R_type;
                    else if (i >= 5 && i < 13) current_ins.type = I_type;
                    else current_ins.type = J_type;
                    break;
                }
                else if (i == 14) current_ins.type = -1;
            }
            switch (current_ins.type)
            {
            case R_type:
                for (int i = 0; i < 3; i++)
                {
                    tok = strtok(NULL, "\t, \n");
                    if (!isdigit(tok[0]) || strlen(tok) > 2 || (strlen(tok) == 2 && !isdigit(tok[1])))
                    {
                        printf("Error occured wihle reading the R_type Instructon!\nIn line: %d used ---> %s\a\n", ins_count - 1, tok);
                        exit(1);
                    }
                    else {
                        int num = (int)(tok[0] - '0');
                        if (strlen(tok) == 2) num = num * 10 + (int)(tok[1] - '0');
                        if (num > 16)
                        {
                            printf("Register Num is out of range!\nIn line: %d used ---> %s\a\n", ins_count - 1, tok);
                            exit(1);
                        }
                        if (i == 0) current_ins.rd = num;
                        else if (i == 1) current_ins.rs = num;
                        else current_ins.rt = num;
                    }
                }
                Rtomachine(&current_ins);
                fprintf(machp, "%d\n", current_ins.int_of_inst);
                break;
            case I_type:
                if (i == 8);
                if (i == 12);
                for (int i = 0; i < 2; i++)
                {
                    tok = strtok(NULL, "\t, \n");
                    if (!isdigit(tok[0]) || strlen(tok) > 2 || (strlen(tok) == 2 && !isdigit(tok[1])))
                    {
                        printf("Error occured wihle reading the I_type Instructon!\nIn line: %d used ---> %s\a\n", ins_count - 1, tok);
                        exit(1);
                    }
                    else {
                        int num = (int)(tok[0] - '0');
                        if (strlen(tok) == 2) num = num * 10 + (int)(tok[1] - '0');
                        if (num > 16)
                        {
                            printf("Register Num is out of range!\nIn line: %d used ---> %s\a\n", ins_count - 1, tok);
                            exit(1);
                        }
                        if (i == 0) current_ins.rt = num;
                        else current_ins.rs = num;
                    }
                }
                if (i == 11)
                {
                    int temp = current_ins.rs;
                    current_ins.rs = current_ins.rt;
                    current_ins.rt = temp;
                }
                tok = strtok(NULL, "\t, \n");
                if (isdigit(tok[0]))
                {
                    int num = 0;
                    for (int j = 0; j < strlen(tok); j++)
                    {
                        num *= 10;
                        num += (int)(tok[j] - '0');
                    }
                    if (num > 32767 || num < -32768)
                    {
                        printf("Immediate value is out of range!\nIn line: %d used ---> %d\a\n", ins_count - 1, num);
                        exit(1);
                    }
                    current_ins.imm = num;
                }
                else
                {
                    int j;
                    for (j = 0; j < symtab_len; j++)
                    {
                        if (strcmp(table[j].symbol, tok) == 0)
                        {
                            current_ins.imm = table[j].value;
                            break;
                        }
                    }
                    if (j == symtab_len)
                    {
                        printf("Symbol wasnt find!\nIn line: %d used ---> %s\a\n", ins_count - 1, tok);
                        exit(1);
                    }
                }
                Itomachine(&current_ins);
                fprintf(machp, "%d\n", current_ins.int_of_inst);
                break;
            }
        }
    }

    fclose(assp);
    fclose(machp);
    return 0;
}
