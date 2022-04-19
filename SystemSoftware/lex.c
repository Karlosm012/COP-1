// Karlos Morales Ramos
// COP 3402
// Lexical Analyzer
// 3/12/22

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "compiler.h"
#define MAX_NUMBER_TOKENS 1000
#define MAX_IDENT_LEN 11
#define MAX_NUMBER_LEN 5

char* resWords[31] = { "==", "const", "!=", "var", "<", "procedure", "<=", "call",
">", "if", ">=", "then", "*", "else", "/", "while", "+", "do", "-", "begin",
"(", "end", ")", "read", ",", "write", ".", "identifier", ";", "number", ":=" };

lexeme *list;
int lex_index;
int inpIndex;
int error;
int varIndex;

void printlexerror(int type);
void printtokens();

void delWhite(char* input);
char* word(char* input);
void resWord(char* input);
int number(char* input);
void begin(char* input);

lexeme *lexanalyzer(char *input, int printFlag)
{
	list = malloc(sizeof(lexeme) * MAX_NUMBER_TOKENS);
	lex_index = 0;

    // start the lex analyzer
	begin(input);

    // if there is an error, return NULL
	if(error)
        exit(1);

	if (printFlag)
		printtokens();

	// these last two lines are really important for the rest of the package to run
	list[lex_index].type = -1;
	return list;
}

// we do not want the whitespaces
void delWhite(char* input)
{
    while(input[inpIndex] == ' ')
        inpIndex++;
}

// if the word is in our reserved list, add it to the token table
void resWord(char* input)
{
    char* string = word(input);

    if(string == NULL)
    {
        printlexerror(1);
        error = 1;
        return;
    }

    // checking string for reserved words and then for identifier
    if(strcmp(string, "const") == 0)
    {
        list[lex_index].type = constsym;
        strcpy(list[lex_index].name, "const");
        lex_index++;
    }

    else if(strcmp(string, "var") == 0)
    {
        list[lex_index].type = varsym;
        strcpy(list[lex_index].name, "var");
        lex_index++;
    }

    else if(strcmp(string, "procedure") == 0)
    {
        list[lex_index].type = procsym;
        strcpy(list[lex_index].name, "procedure");
        lex_index++;
    }

    else if(strcmp(string, "call") == 0)
    {
        list[lex_index].type = callsym;
        strcpy(list[lex_index].name, "call");
        lex_index++;
    }

    else if(strcmp(string, "if") == 0)
    {
        list[lex_index].type = ifsym;
        strcpy(list[lex_index].name, "if");
        lex_index++;
    }

    else if(strcmp(string, "then") == 0)
    {
        list[lex_index].type = thensym;
        strcpy(list[lex_index].name, "then");
        lex_index++;
    }

    else if(strcmp(string, "else") == 0)
    {
        list[lex_index].type = elsesym;
        strcpy(list[lex_index].name, "else");
        lex_index++;
    }

    else if(strcmp(string, "while") == 0)
    {
        list[lex_index].type = whilesym;
        strcpy(list[lex_index].name, "while");
        lex_index++;
    }

    else if(strcmp(string, "do") == 0)
    {
        list[lex_index].type = dosym;
        strcpy(list[lex_index].name, "do");
        lex_index++;
    }

    else if(strcmp(string, "begin") == 0)
    {
        list[lex_index].type = beginsym;
        strcpy(list[lex_index].name, "begin");
        lex_index++;
    }

    else if(strcmp(string, "end") == 0)
    {
        list[lex_index].type = endsym;
        strcpy(list[lex_index].name, "end");
        lex_index++;
    }

    else if(strcmp(string, "read") == 0)
    {
        list[lex_index].type = readsym;
        strcpy(list[lex_index].name, "read");
        lex_index++;
    }

    else if(strcmp(string, "write") == 0)
    {
        list[lex_index].type = writesym;
        strcpy(list[lex_index].name, "write");
        lex_index++;
    }

    else
    {
        list[lex_index].type = identsym;
        strcpy(list[lex_index].name, string);
        lex_index++;
    }
}

// check word to see if it's correct length
char* word(char* input)
{
    if(input[inpIndex] == ' ')
        delWhite(input);

    int len = 0;

    // store starting letter index
    int wordIndex = inpIndex;

    // if the input is an alpha we add to len and increase index
    while(isalpha(input[inpIndex]) != 0 || isdigit(input[inpIndex]) != 0)
    {
        len++;
        inpIndex++;
    }

    // if greater than MAX_IDENT_LEN, hit error
    if(len > MAX_IDENT_LEN)
    {
        printlexerror(3);
        error = 1;
    }

    // create a string memory for our word
    char* string = malloc(sizeof(char) * len);

    // place letters inside the string
    for(int i = 0; i < len; i++)
        string[i] = input[wordIndex + i];

    return string;
}

int number(char* input)
{
    // store the starting number index
    int numIndex = inpIndex;

    while(isdigit(input[inpIndex]) != 0)
    {
        inpIndex++;
    }

    // create a string memory for our number
    char* string = malloc(sizeof(char) * (inpIndex - numIndex));
    if(inpIndex - numIndex < MAX_NUMBER_LEN)
    {
        // we place the numbers inside string
        for(int i = 0; i < inpIndex - numIndex; i++)
        {
            string[i] = input[numIndex + i];
        }

        // if next character is a letter, hit error
        if(isalpha(input[inpIndex]) != 0)
        {
            printlexerror(1);
            error = 1;
            return 0;
        }

        return atoi(string);
    }

    // if it's greater tan MAX_NUMBER_LEN, hit error
    printlexerror(2);
    error = 1;
    return -1;
}

void begin(char* input)
{
    while(input[inpIndex] != '\0')
    {
        int num;
        // this will skip control characters
        if(iscntrl(input[inpIndex]) || isspace(input[inpIndex]))
            inpIndex++;

        // we have found a number
        else if(isdigit(input[inpIndex]) != 0)
        {
            num = number(input);
            list[lex_index].type = numbersym;
            list[lex_index].value = num;
            lex_index++;
        }


        // we have found a letter
        else if(isalpha(input[inpIndex]) != 0)
            resWord(input);

        else
        {
            switch(input[inpIndex])
            {
            case'=':
                // for equal
                if(input[inpIndex + 1] == '=')
                {
                    list[lex_index].type = eqlsym;
                    lex_index++;
                    inpIndex += 2;
                }

                // equal sign alone is not a valid symbol
                else
                {
                    printlexerror(4);
                    error = 1;
                    inpIndex++;
                }

                break;

            case '!':
                // for not equal
                if(input[inpIndex + 1] == '=')
                {
                    list[lex_index].type = neqsym;
                    lex_index++;
                    inpIndex += 2;
                }

                // exclamation mark alone is not a valid symbol
                else
                {
                    printlexerror(4);
                    error = 1;
                    inpIndex++;
                }

                break;

            case '<':
                // for less than or equal
                if(input[inpIndex + 1] == '=')
                {
                    list[lex_index].type = leqsym;
                    lex_index++;
                    inpIndex += 2;
                }

                // for less than
                else
                {
                    list[lex_index].type = lsssym;
                    lex_index++;
                    inpIndex++;
                }

                break;

            case '>':
                // for greater than or equal
                if(input[inpIndex + 1] == '=')
                {
                    list[lex_index].type = geqsym;
                    lex_index++;
                    inpIndex += 2;
                }

                // for greater than
                else
                {
                    list[lex_index].type = gtrsym;
                    lex_index++;
                    inpIndex++;
                }

                break;

            case '*':
                list[lex_index].type = multsym;
                lex_index++;
                inpIndex++;
                break;

            case '/':
                if(input[inpIndex + 1] == '*')
                {
                    int inLen = strlen(input);
                    // skip comments
                    inpIndex += 2;
                    while((input[inpIndex] != '*' && input[inpIndex + 1] != '/') || (input[inpIndex] == '*' && input[inpIndex + 1] != '/'))
                    {
                        inpIndex++;
                        if(inpIndex == inLen)
                        {
                            printlexerror(5);
                            error = 1;
                        }
                    }

                    // start after the comment enders
                    inpIndex += 2;

                    // add to continue
                    inpIndex++;
                }

                else
                {
                    list[lex_index].type = divsym;
                    lex_index++;
                    inpIndex++;
                }

                break;

            case '+':
                list[lex_index].type = plussym;
                lex_index++;
                inpIndex++;
                break;

            case '-':
                list[lex_index].type = minussym;
                lex_index++;
                inpIndex++;
                break;

            case '(':
                list[lex_index].type = lparensym;
                lex_index++;
                inpIndex++;
                break;

            case ')':
                list[lex_index].type = rparensym;
                lex_index++;
                inpIndex++;
                break;

            case ',':
                list[lex_index].type = commasym;
                lex_index++;
                inpIndex++;
                break;

            case '.':
                list[lex_index].type = periodsym;
                lex_index++;
                inpIndex++;
                break;

            case ';':
                list[lex_index].type = semicolonsym;
                lex_index++;
                inpIndex++;
                break;

            case ':':
                // for assign
                if(input[inpIndex + 1] == '=')
                {
                    list[lex_index].type = assignsym;
                    lex_index++;
                    inpIndex += 2;
                }

                // if not equal sign after, invalid symbol
                else
                {
                    printlexerror(4);
                    error = 1;
                    inpIndex++;
                }

                break;

            // if its whitespace, we increment input
            case ' ':
                delWhite(input);
                break;

            // default are invalid symbols
            default:
                printlexerror(4);
                error = 1;
                input++;
                break;

            }
        }

        if(error)
            break;
    }
}

void printtokens()
{
	int i;
	printf("Lexeme Table:\n");
	printf("lexeme\t\ttoken type\n");
	for (i = 0; i < lex_index; i++)
	{
		switch (list[i].type)
		{
			case eqlsym:
				printf("%11s\t%d", "==", eqlsym);
				break;
			case neqsym:
				printf("%11s\t%d", "!=", neqsym);
				break;
			case lsssym:
				printf("%11s\t%d", "<", lsssym);
				break;
			case leqsym:
				printf("%11s\t%d", "<=", leqsym);
				break;
			case gtrsym:
				printf("%11s\t%d", ">", gtrsym);
				break;
			case geqsym:
				printf("%11s\t%d", ">=", geqsym);
				break;
			case multsym:
				printf("%11s\t%d", "*", multsym);
				break;
			case divsym:
				printf("%11s\t%d", "/", divsym);
				break;
			case plussym:
				printf("%11s\t%d", "+", plussym);
				break;
			case minussym:
				printf("%11s\t%d", "-", minussym);
				break;
			case lparensym:
				printf("%11s\t%d", "(", lparensym);
				break;
			case rparensym:
				printf("%11s\t%d", ")", rparensym);
				break;
			case commasym:
				printf("%11s\t%d", ",", commasym);
				break;
			case periodsym:
				printf("%11s\t%d", ".", periodsym);
				break;
			case semicolonsym:
				printf("%11s\t%d", ";", semicolonsym);
				break;
			case assignsym:
				printf("%11s\t%d", ":=", assignsym);
				break;
			case beginsym:
				printf("%11s\t%d", "begin", beginsym);
				break;
			case endsym:
				printf("%11s\t%d", "end", endsym);
				break;
			case ifsym:
				printf("%11s\t%d", "if", ifsym);
				break;
			case thensym:
				printf("%11s\t%d", "then", thensym);
				break;
			case elsesym:
				printf("%11s\t%d", "else", elsesym);
				break;
			case whilesym:
				printf("%11s\t%d", "while", whilesym);
				break;
			case dosym:
				printf("%11s\t%d", "do", dosym);
				break;
			case callsym:
				printf("%11s\t%d", "call", callsym);
				break;
			case writesym:
				printf("%11s\t%d", "write", writesym);
				break;
			case readsym:
				printf("%11s\t%d", "read", readsym);
				break;
			case constsym:
				printf("%11s\t%d", "const", constsym);
				break;
			case varsym:
				printf("%11s\t%d", "var", varsym);
				break;
			case procsym:
				printf("%11s\t%d", "procedure", procsym);
				break;
			case identsym:
				printf("%11s\t%d", list[i].name, identsym);
				break;
			case numbersym:
				printf("%11d\t%d", list[i].value, numbersym);
				break;
		}
		printf("\n");
	}
	printf("\n");
	printf("Token List:\n");
	for (i = 0; i < lex_index; i++)
	{
		if (list[i].type == numbersym)
			printf("%d %d ", numbersym, list[i].value);
		else if (list[i].type == identsym)
			printf("%d %s ", identsym, list[i].name);
		else
			printf("%d ", list[i].type);
	}
	printf("\n");
}

void printlexerror(int type)
{
	if (type == 1)
		printf("Lexical Analyzer Error: Invalid Identifier\n");
	else if (type == 2)
		printf("Lexical Analyzer Error: Number Length\n");
	else if (type == 3)
		printf("Lexical Analyzer Error: Identifier Length\n");
	else if (type == 4)
		printf("Lexical Analyzer Error: Invalid Symbol\n");
	else if (type == 5)
		printf("Lexical Analyzer Error: Never-ending comment\n");
	else
		printf("Implementation Error: Unrecognized Error Type\n");

    free(list);
	return;
}
