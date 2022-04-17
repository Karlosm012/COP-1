// Karlos Morales Ramos
// COP 3402
// Virtual Machine
// 3/12/22

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"
#define MAX_REG_LENGTH 10
#define MAX_DATA_LENGTH 50
#define MAX_PROGRAM_LENGTH 150


// Globals
int pc = 0;
int bp = 0;
int sp = -1;
int rp = MAX_REG_LENGTH;
instruction* ir;

int stack[MAX_DATA_LENGTH] = {0};
int rStack[MAX_REG_LENGTH] = {0};

int halt = 0;
int line = 0;

char opName[4];

// functions
int base(int L, int BP, int *data_stack);
void fetch(instruction* code);
void execute();
void execute_program(instruction* code, int printFlag);
void print_execution(int line, char *opname, instruction IR, int PC, int BP, int
SP, int RP, int *data_stack, int *register_stack);


void fetch(instruction* code)
{
    ir = &code[pc];
    pc = pc + 1;
}

void execute()
{
    switch(ir->opcode)
    {

    // LIT
    case 1:
        strcpy(opName, "LIT");
        rp = rp - 1;
        rStack[rp] = ir->m;
        break;

    // OPR
    case 2:
        switch(ir->m)
        {

        // RTN
        case 0:
            strcpy(opName, "RET");
            sp = bp - 1;
            pc = stack[sp + 3];
            bp = stack[sp + 2];
            break;

        // NEG
        case 1:
            strcpy(opName, "NEG");
            rStack[rp] = -rStack[rp];
            break;

        // ADD
        case 2:
            strcpy(opName, "ADD");
            rp = rp + 1;
            rStack[rp] = rStack[rp] + rStack[rp - 1];
            break;

        // SUB
        case 3:
            strcpy(opName, "SUB");
            rp = rp + 1;
            rStack[rp] = rStack[rp] - rStack[rp - 1];
            break;

        // MUL
        case 4:
            strcpy(opName, "MUL");
            rp = rp + 1;
            rStack[rp] = rStack[rp] * rStack[rp - 1];
            break;

        // DIV
        case 5:
            strcpy(opName, "DIV");
            rp = rp + 1;
            rStack[rp] = rStack[rp] / rStack[rp - 1];
            break;

        // EQL
        case 6:
            strcpy(opName, "EQL");
            rp = rp + 1;
            rStack[rp] = rStack[rp] == rStack[rp - 1];
            break;

        // NEQ
        case 7:
            strcpy(opName, "NEQ");
            rp = rp + 1;
            rStack[rp] = rStack[rp] != rStack[rp - 1];
            break;

        // LSS
        case 8:
            strcpy(opName, "LSS");
            rp = rp + 1;
            rStack[rp] = rStack[rp] < rStack[rp - 1];
            break;

        // LEQ
        case 9:
            strcpy(opName, "LEQ");
            rp = rp + 1;
            rStack[rp] = rStack[rp] <= rStack[rp - 1];
            break;

        // GTR
        case 10:
            strcpy(opName, "GTR");
            rp = rp + 1;
            rStack[rp] = rStack[rp] > rStack[rp - 1];
            break;

        // GEQ
        case 11:
            strcpy(opName, "GEQ");
            rp = rp + 1;
            rStack[rp] = rStack[rp] >= rStack[rp - 1];
            break;
        }

        break;

    // LOD
    case 3:
        strcpy(opName, "LOD");
        rp = rp - 1;
        rStack[rp] = stack[base(ir->l, bp, stack) + ir->m];
        break;

    // STO
    case 4:
        strcpy(opName, "STO");
        stack[base(ir->l, bp, stack) + ir->m] = rStack[rp];
        if(rp != MAX_REG_LENGTH);
            rp = rp + 1;
        break;

    // CAL
    case 5:
        strcpy(opName, "CAL");
        stack[sp + 1] = base(ir->l, bp, stack);
        stack[sp + 2] = bp;
        stack[sp + 3] = pc;
        bp = sp + 1;
        pc = ir->m;
        break;

    // INC
    case 6:
        strcpy(opName, "INC");
        sp = sp + ir->m;
        break;

    // JMP
    case 7:
        strcpy(opName, "JMP");
        pc = ir->m;
        break;

    // JPC
    case 8:
        strcpy(opName, "JPC");
        if(rStack[MAX_REG_LENGTH - 1] == 0)
            pc = ir->m;


        if(rp != MAX_REG_LENGTH)
            rp = rp + 1;
        break;

    // WRT
    case 9:
        switch(ir->m)
        {
        // WRT
        case 1:
            strcpy(opName, "WRT");
            printf("Top of the stack value: %d\n", rStack[rp]);
            if(rp != MAX_REG_LENGTH)
                rp = rp + 1;
            break;

        // RED
        case 2:
            strcpy(opName, "RED");
            rp--;
            printf("Please Enter an Integer: \n");
            scanf("%d", &rStack[rp]);
            break;

        case 3:
            strcpy(opName, "HAL");
            halt = 1;
            break;
        }
        break;
    }
}

int base(int L, int BP, int *data_stack)
{
    int ctr = L;
    int rtn = BP;

    while (ctr > 0)
    {
        rtn = data_stack[rtn];
        ctr--;
    }

    return rtn;
}

void execute_program(instruction *code, int printFlag)
{
    if (printFlag)
    {
        printf("\t\t\t\tPC\tBP\tSP\tRP\n");
        printf("Initial values:\t\t\t%d\t%d\t%d\t%d\n", pc, bp, sp, rp);
    }

    while(halt == 0)
    {
        fetch(code);

        line = pc - 1;

        execute();

        if(printFlag)
            print_execution(line, opName, *ir, pc, bp, sp, rp, stack, rStack);

    }

    return;
}

void print_execution(int line, char *opname, instruction IR, int PC, int BP, int
SP, int RP, int *data_stack, int *register_stack)
{
    int i;

    // print out instruction and registers
    printf("%2d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t\t", line, opname, IR.l, IR.m, PC,
BP, SP, RP);

    // print register stack
    for (i = MAX_REG_LENGTH - 1; i >= RP; i--)
        printf("%d ", register_stack[i]);
    printf("\n");

    // print data stack
    printf("\tdata stack : ");
    for (i = 0; i <= SP; i++)
            printf("%d ", data_stack[i]);
    printf("\n");
}
