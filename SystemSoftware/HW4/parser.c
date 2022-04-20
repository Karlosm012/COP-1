// Karlos Morales Ramos
// COP 3402
// 4/7/22
// Parser

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compiler.h"

#define MAX_CODE_LENGTH 150
#define MAX_SYMBOL_COUNT 50
#define MAX_REG_HEIGHT 10

// code with code index
instruction *code;
int cIndex;

// symbol with table index
symbol *table;
int tIndex;

// tokens with token index
lexeme* token;
int tokIndex;

// keep track of level
int level;

// keep track of stack register
int counterVar = 0;

// skeleton functions
void emit(int opname, int level, int mvalue);
void addToSymbolTable(int k, char n[], int v, int l, int a, int m);
void mark();
int multipledeclarationcheck(char name[]);
int findsymbol(char name[], int kind);
void printparseerror(int err_code);
void printsymboltable();
void printassemblycode();

// parse functions
void program(lexeme *list);
void block(lexeme *list);
void gToken(lexeme *list);
void constant(lexeme *list);
int variable(lexeme *list);
void procedure(lexeme *list);
void statement(lexeme *list);
void logic(lexeme* list);
void condition(lexeme *list);
void expression(lexeme *list);
void term(lexeme *list);
void factor(lexeme *list);


instruction *parse(lexeme *list, int printTable, int printCode)
{
	code = malloc(sizeof(instruction) * MAX_CODE_LENGTH);
	table = malloc(sizeof(symbol) * MAX_SYMBOL_COUNT);
	tIndex = 0;
	cIndex = 0;

	tokIndex = 0;

	program(list);

	if (printTable)
		printsymboltable();
	if (printCode)
		printassemblycode();

	code[cIndex].opcode = -1;

	return code;
}

void program(lexeme *list)
{
    // JMP
    emit(7, 0, 0);

    addToSymbolTable(3, "main", 0, 0, 0, 0);
    level = -1;

    gToken(list);
    block(list);

    if(token->type != periodsym)
    {
        printparseerror(1);
        exit(1);
    }

    else
    {
        // HALT
        emit(9, 0, 3);
    }

    // we placed in code[i].m the index of the procedure in the table,
    // now we use that index to get the address in the table and correct
    // the code[i].m
    for(int i = 0; i < cIndex; i++)
        if(code[i].opcode == 5)
            code[i].m = table[code[i].m].addr;

    // change the m value of the jmp to the addr in "main"
    code[0].m = table[0].addr;
}

void gToken(lexeme *list)
{
    token = &list[tokIndex];
    tokIndex++;
}

void block(lexeme *list)
{
    // x's going to be to reserve SL, DL, RA
    int x = 3;

    // tIndex - 1 is our "main"
    int jmpIndex = tIndex-1;

    // increment level
    level++;

    // constants
    if(token->type == constsym)
        constant(list);

    // variables
    if(token->type == varsym)
        x += variable(list);

    // procedures
    while(token->type == procsym)
        procedure(list);

    // marks address of "main" with where the program begins
    table[jmpIndex].addr = cIndex;

    // INC
    emit(6, 0, x);

    statement(list);

    // mark the symbols we used
    mark();

    // decrement level
    level--;
}

void constant(lexeme *list)
{
    do
    {
        // gets identifier
        gToken(list);

        lexeme* ident = token;

        if(token->type != identsym)
        {
            printparseerror(2);
            exit(1);
        }

        int b = multipledeclarationcheck(token->name);
        if(b != -1)
        {
            printparseerror(18);
            exit(1);
        }

        // gets assign token
        gToken(list);
        if(token->type != assignsym)
        {
            printparseerror(2);
            exit(1);
        }

        // gets number symbol
        gToken(list);
        if(token->type != numbersym)
        {
            printparseerror(2);
            exit(1);
        }

        addToSymbolTable(1, ident->name, token->value, level, 0, 0);
        gToken(list);
    } while(token->type == commasym);

    if(token->type != semicolonsym)
    {
        if(token->type == identsym)
        {
            printparseerror(13);
            exit(1);
        }

        else
        {
            printparseerror(14);
            exit(1);
        }
    }

    // gets next token
    gToken(list);
}

int variable(lexeme *list)
{
    // number of variables we need in the AR
    int numVar = 0;
    int space = 2;

    do
    {
        numVar++;

        // gets identifier
        gToken(list);
        if(token->type != identsym)
        {
            printparseerror(3);
            exit(1);
        }

        int b = multipledeclarationcheck(token->name);
        if(b != -1)
        {
            printparseerror(18);
            exit(1);
        }

        addToSymbolTable(2, token->name, 0, level, numVar + space, 0);

        gToken(list);

    } while(token->type == commasym);


    if(token->type != semicolonsym)
    {
        // is an identifier error
        if(token->type == identsym)
        {
            printparseerror(13);
            exit(1);
        }

        // not an identifier error
        else
        {
            printparseerror(14);
            exit(1);
        }
    }

    // gets next token
    gToken(list);

    return numVar;
}

void procedure(lexeme *list)
{
    // gets identifier
    gToken(list);

    if(token->type != identsym)
    {
        printparseerror(4);
        exit(1);
    }

    int b = multipledeclarationcheck(token->name);
    if(b != -1)
    {
        printparseerror(18);
        exit(1);
    }

    addToSymbolTable(3, token->name, 0, level, 0, 0);

    // gets semicolon
    gToken(list);
    if(token->type != semicolonsym)
    {
        printparseerror(4);
        exit(1);
    }

    // gets next token
    gToken(list);

    // goes to block
    block(list);

    if(token->type != semicolonsym)
    {
        printparseerror(14);
        exit(1);
    }

    // RET
    //important because this marks the jmp address
    emit(2, 0, 0);

    // gets next token
    gToken(list);
}

void statement(lexeme *list)
{
    // identifier symbol
    if(token->type == identsym)
    {
        int a = findsymbol(token->name, 2);
        if(a == -1)
        {
            if(findsymbol(token->name, 1) > -1 || findsymbol(token->name, 3) > -1)
            {
                printparseerror(6);
                exit(1);
            }

            printparseerror(19);
            exit(1);
        }

        // gets assign token
        gToken(list);
        if(token->type != assignsym)
        {
            printparseerror(5);
            exit(1);
        }

        // gets next token
        gToken(list);

        // starts expression
        expression(list);

        // STO
        emit(4, level - table[a].level, table[a].addr);
        counterVar--;
    }

    // begin symbol
    else if(token->type == beginsym)
    {
        do
        {
            // gets next token
            gToken(list);

            // starts statement
            statement(list);

        } while(token->type == semicolonsym);

        if(token->type != endsym)
        {
            if(token->type == identsym || token->type == readsym || token->type == writesym ||
               token->type == beginsym || token->type == callsym || token->type == ifsym ||
               token->type == whilesym)
            {
                printparseerror(15);
                exit(1);
            }

            printparseerror(16);
            exit(1);
        }

        // gets next token
        gToken(list);
    }

    // if symbol
    else if(token->type == ifsym)
    {
        logic(list);

        int jpcIdx = cIndex;

        // JPC
        emit(8, 0, jpcIdx);
        counterVar--;

        if(token->type != thensym)
        {
            printparseerror(8);
            exit(1);
        }

        gToken(list);
        statement(list);

        if(token->type == elsesym)
        {
            int jmpIdx = cIndex;

            // JMP
            emit(7, 0, jmpIdx);

            code[jpcIdx].m = cIndex;

            gToken(list);
            statement(list);

            code[jmpIdx].m = cIndex;
        }

        else
            code[jpcIdx].m = cIndex;
    }

    // while symbol
    else if(token->type == whilesym)
    {
        int loopIdx = cIndex;

        logic(list);

        if(token->type != dosym)
        {
            printparseerror(9);
            exit(1);
        }
        gToken(list);
        int jpcIdx = cIndex;

        // JPC
        emit(8, 0, 0);
        counterVar--;

        statement(list);

        // JMP
        emit(7, 0, loopIdx);

        code[jpcIdx].m = cIndex;
    }

    // read symbol
    else if(token->type == readsym)
    {
        gToken(list);

        if(token->type != identsym)
        {
            printparseerror(6);
            exit(1);
        }

        int a = findsymbol(token->name, 2);
        if(a == -1)
        {
            if(findsymbol(token->name, 1) > -1 || findsymbol(token->name, 3) > -1)
            {
                printparseerror(6);
                exit(1);
            }

            printparseerror(19);
            exit(1);
        }

        // RED
        emit(9, 0, 2);
        counterVar++;

        if(counterVar > MAX_REG_HEIGHT)
        {
            printparseerror(20);
            exit(1);
        }

        // STO
        emit(4, level - table[a].level, table[a].addr);
        counterVar--;

        gToken(list);
    }

    // write symbol
    else if(token->type == writesym)
    {
        gToken(list);

        expression(list);

        // WRT
        emit(9, 0, 1);
    }

    // call symbol
    else if(token->type == callsym)
    {
        gToken(list);

        if(token->type != identsym)
        {
            printparseerror(7);
            exit(1);
        }

        int a = findsymbol(token->name, 3);
        if(a == -1)
        {
            if(findsymbol(token->name, 1) > -1 || findsymbol(token->name, 2) > -1)
            {
                printparseerror(7);
                exit(1);
            }

            printparseerror(19);
            exit(1);
        }

        // CAL
        emit(5, level - table[a].level, a);

        // gets next token
        gToken(list);
    }
}

void logic(lexeme* list)
{
    gToken(list);

    if(token->type == notsym)
    {
        gToken(list);
        condition(list);

        // NOT
        emit(2, 0, 14);
    }

    else
    {
        condition(list);
        while(token->type == andsym || token->type == orsym)
        {
            if(token->type == andsym)
            {
                gToken(list);
                condition(list);

                // AND
                emit(2, 0 ,12);
                counterVar--;
            }

            else
            {
                gToken(list);
                condition(list);

                // ORR
                emit(2, 0, 13);
                counterVar--;
            }
        }
    }
}

void condition(lexeme* list)
{
    if(token->type == lparensym)
    {
        logic(list);

        if(token->type != rparensym)
        {
            printparseerror(12);
            exit(1);
        }

        gToken(list);
    }

    else
    {
        expression(list);
        if(token->type == eqlsym)
        {
            gToken(list);
            expression(list);

            // EQL
            emit(2, 0, 6);
            counterVar--;
        }

        else if(token->type == neqsym)
        {
            gToken(list);
            expression(list);

            // NEQ
            emit(2, 0, 7);
            counterVar--;
        }

        else if(token->type == lsssym)
        {
            gToken(list);
            expression(list);

            // LSS
            emit(2, 0, 8);
            counterVar--;
        }

        else if(token->type == leqsym)
        {
            gToken(list);
            expression(list);

            // LEQ
            emit(2, 0, 9);
            counterVar--;
        }

        else if(token->type == gtrsym)
        {
            gToken(list);
            expression(list);

            // GTR
            emit(2, 0, 10);
            counterVar--;
        }

        else if(token->type == geqsym)
        {
            gToken(list);
            expression(list);

            // GEQ
            emit(2, 0, 11);
            counterVar--;
        }

        else
        {
            printparseerror(10);
            exit(1);
        }
    }
}

// might need to be rewritten
void expression(lexeme* list)
{
    if(token->type == minussym)
    {
        gToken(list);
        term(list);

        // NEG
        emit(2, 0, 1);

        while(token->type == plussym || token->type == minussym)
        {
            if(token->type == plussym)
            {
                gToken(list);
                term(list);

                // ADD
                emit(2, 0, 2);
                counterVar--;
            }

            else
            {
                gToken(list);
                term(list);

                // SUB
                emit(2, 0, 3);
                counterVar--;
            }
        }

    }

    else
    {
        if(token->type == plussym)
            gToken(list);

        term(list);

        while(token->type == plussym || token->type == minussym)
        {
            if(token->type == plussym)
            {
                gToken(list);
                term(list);

                // ADD
                emit(2, 0, 2);
                counterVar--;
            }

            else
            {
                gToken(list);
                term(list);

                // SUB
                emit(2, 0, 3);
                counterVar--;
            }
        }
    }
}

void term(lexeme* list)
{
    factor(list);

    while(token->type == multsym || token->type == divsym)
    {
        if(token->type == multsym)
        {
            gToken(list);
            factor(list);

            // MUL
            emit(2, 0, 4);
            counterVar--;
        }

        else
        {
            gToken(list);
            factor(list);

            // DIV
            emit(2, 0, 5);
            counterVar--;
        }
    }
}

void factor(lexeme* list)
{
    if(token->type == identsym)
    {
        // index
        int a;

        // checks for constant or variable
        int constA = findsymbol(token->name, 1);
        int varB = findsymbol(token->name, 2);

        if(constA > varB)
            a = constA;
        else
            a = varB;

        if(a == -1)
        {
            if(findsymbol(token->name, 3) > -1)
            {
                printparseerror(11);
                exit(1);
            }
            printparseerror(19);
            exit(1);
        }

        // if kind equals constant
        if(table[a].kind == 1)
        {
            // LIT
            emit(1, 0, table[a].val);
            counterVar++;

            if(counterVar > MAX_REG_HEIGHT)
            {
                printparseerror(20);
                exit(1);
            }

            gToken(list);
        }

        // if kind equals variable
        else if(table[a].kind == 2)
        {
            // LOD
            emit(3, level - table[a].level, table[a].addr);
            counterVar++;

            if(counterVar > MAX_REG_HEIGHT)
            {
                printparseerror(20);
                exit(1);
            }

            gToken(list);
        }
    }

    else if(token->type == numbersym)
    {
        // LIT
        emit(1, 0, token->value);
        counterVar++;

        if(counterVar > MAX_REG_HEIGHT)
        {
            printparseerror(20);
            exit(1);
        }

        gToken(list);
    }

    else if(token->type == lparensym)
    {
        gToken(list);
        expression(list);

        if(token->type != rparensym)
        {
            printparseerror(12);
            exit(1);
        }

        gToken(list);
    }

    else
    {
        printparseerror(11);
        exit(1);
    }
}

// adds a line of code to the program
void emit(int opname, int level, int mvalue)
{
	code[cIndex].opcode = opname;
	code[cIndex].l = level;
	code[cIndex].m = mvalue;
	cIndex++;
}

// add a symbol to the symbol table
void addToSymbolTable(int k, char n[], int v, int l, int a, int m)
{
	table[tIndex].kind = k;
	strcpy(table[tIndex].name, n);
	table[tIndex].val = v;
	table[tIndex].level = l;
	table[tIndex].addr = a;
	table[tIndex].mark = m;
	tIndex++;
}

// mark the symbols belonging to the current procedure, should be called at the end of block
void mark()
{
	int i;
	for (i = tIndex - 1; i >= 0; i--)
	{
		if (table[i].mark == 1)
			continue;
		if (table[i].level < level)
			return;
		table[i].mark = 1;
	}
}

// checks if a new symbol has a valid name, by checking if there's an existing symbol
// with the same name in the procedure
int multipledeclarationcheck(char name[])
{
	int i;
	for (i = 0; i < tIndex; i++)
		if (table[i].mark == 0 && table[i].level == level && strcmp(name, table[i].name) == 0)
            return i;

	return -1;
}

// returns the index of a symbol with a given name and in the symbol table
// returns -1 if not found
// prioritizes lower lex levels
int findsymbol(char name[], int kind)
{
	int i;
	int max_idx = -1;
	int max_lvl = -1;
	for (i = 0; i < tIndex; i++)
	{
		if (table[i].mark == 0 && table[i].kind == kind && strcmp(name, table[i].name) == 0)
		{
			if (max_idx == -1 || table[i].level > max_lvl)
			{
				max_idx = i;
				max_lvl = table[i].level;
			}
		}
	}
	return max_idx;
}

void printparseerror(int err_code)
{
	switch (err_code)
	{
		case 1:
			printf("Parser Error: Program must be closed by a period\n");
			break;
		case 2:
			printf("Parser Error: Constant declarations should follow the pattern 'ident := number {, ident := number}'\n");
			break;
		case 3:
			printf("Parser Error: Variable declarations should follow the pattern 'ident {, ident}'\n");
			break;
		case 4:
			printf("Parser Error: Procedure declarations should follow the pattern 'ident ;'\n");
			break;
		case 5:
			printf("Parser Error: Variables must be assigned using :=\n");
			break;
		case 6:
			printf("Parser Error: Only variables may be assigned to or read\n");
			break;
		case 7:
			printf("Parser Error: call must be followed by a procedure identifier\n");
			break;
		case 8:
			printf("Parser Error: if must be followed by then\n");
			break;
		case 9:
			printf("Parser Error: while must be followed by do\n");
			break;
		case 10:
			printf("Parser Error: Relational operator missing from condition\n");
			break;
		case 11:
			printf("Parser Error: Arithmetic expressions may only contain arithmetic operators, numbers, parentheses, constants, and variables\n");
			break;
		case 12:
			printf("Parser Error: ( must be followed by )\n");
			break;
		case 13:
			printf("Parser Error: Multiple symbols in variable and constant declarations must be separated by commas\n");
			break;
		case 14:
			printf("Parser Error: Symbol declarations should close with a semicolon\n");
			break;
		case 15:
			printf("Parser Error: Statements within begin-end must be separated by a semicolon\n");
			break;
		case 16:
			printf("Parser Error: begin must be followed by end\n");
			break;
		case 17:
			printf("Parser Error: Bad arithmetic\n");
			break;
		case 18:
			printf("Parser Error: Conflicting symbol declarations\n");
			break;
		case 19:
			printf("Parser Error: Undeclared identifier\n");
			break;
		case 20:
			printf("Parser Error: Register Overflow Error\n");
			break;
		default:
			printf("Implementation Error: unrecognized error code\n");
			break;
	}

	free(code);
	free(table);
}

void printsymboltable()
{
	int i;
	printf("Symbol Table:\n");
	printf("Kind | Name        | Value | Level | Address | Mark\n");
	printf("---------------------------------------------------\n");
	for (i = 0; i < tIndex; i++)
		printf("%4d | %11s | %5d | %5d | %5d | %5d\n", table[i].kind, table[i].name, table[i].val, table[i].level, table[i].addr, table[i].mark);

	free(table);
	table = NULL;
}

void printassemblycode()
{
	int i;
	printf("Line\tOP Code\tOP Name\tL\tM\n");
	for (i = 0; i < cIndex; i++)
	{
		printf("%d\t", i);
		printf("%d\t", code[i].opcode);
		switch (code[i].opcode)
		{
			case 1:
				printf("LIT\t");
				break;
			case 2:
				switch (code[i].m)
				{
					case 0:
						printf("RET\t");
						break;
					case 1:
						printf("NEG\t");
						break;
					case 2:
						printf("ADD\t");
						break;
					case 3:
						printf("SUB\t");
						break;
					case 4:
						printf("MUL\t");
						break;
					case 5:
						printf("DIV\t");
						break;
					case 6:
						printf("EQL\t");
						break;
					case 7:
						printf("NEQ\t");
						break;
					case 8:
						printf("LSS\t");
						break;
					case 9:
						printf("LEQ\t");
						break;
					case 10:
						printf("GTR\t");
						break;
					case 11:
						printf("GEQ\t");
						break;
                    case 12:
                        printf("AND\t");
                        break;
                    case 13:
                        printf("ORR\t");
                        break;
                    case 14:
                        printf("NOT\t");
                        break;
					default:
						printf("err\t");
						break;
				}
				break;
			case 3:
				printf("LOD\t");
				break;
			case 4:
				printf("STO\t");
				break;
			case 5:
				printf("CAL\t");
				break;
			case 6:
				printf("INC\t");
				break;
			case 7:
				printf("JMP\t");
				break;
			case 8:
				printf("JPC\t");
				break;
			case 9:
				switch (code[i].m)
				{
					case 1:
						printf("WRT\t");
						break;
					case 2:
						printf("RED\t");
						break;
					case 3:
						printf("HAL\t");
						break;
					default:
						printf("err\t");
						break;
				}
				break;
			default:
				printf("err\t");
				break;
		}
		printf("%d\t%d\n", code[i].l, code[i].m);
	}
	if (table != NULL)
		free(table);
}
