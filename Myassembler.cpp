#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define R_type 1
#define I_type 2
#define J_type 3

const char* inst[] = {"add","sub","slt","or","nand","addi","slti","ori","lui","lw","sw","beq","jalr","j","halt"};

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



    fclose(assp);
    fclose(machp);
    return 0;
}
