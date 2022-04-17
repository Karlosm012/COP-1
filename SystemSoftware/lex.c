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
"(", "end", ")", "read", ",", "write", ".", "identifiers", ";", "numbers", ":=" };

lexeme *list;
int lex_index;

void printlexerror(int type);
void printtokens();
int checkString(char* string, int i);

lexeme *lexanalyzer(char *input, int printFlag)
{
    strcat(input, " ");
    int inLen = strlen(input);

	list = malloc(sizeof(lexeme) * MAX_NUMBER_TOKENS);
	lex_index = 0;

	char string[50] = {'\0'};

	int i = 0;
	int j = 0;
	int result;

	while(i != inLen)
    {

        // checks comments
        if(input[i] == '/' && input[i+1] == '*')
        {
            // start after the comment initiators
            i += 2;
            while((input[i] != '*' && input[i+1] != '/') || (input[i] == '*' && input[i+1] != '/'))
            {
                i++;
                if(i == inLen)
                {
                    printlexerror(5);
                    exit(1);
                }
            }
            // start after the comment enders
            i += 2;

            // add to continue;
            i++;
        }

        // letters
        else if(isalpha(input[i]))
        {
            string[j] = input[i];
            j++;
            i++;
        }

        // numbers
        else if(isdigit(input[i]))
        {
            string[j] = input[i];
            j++;
            i++;
        }

        // symbols
        else if(!isalpha(input[i]) && !isdigit(input[i]) && !isspace(input[i]) && !iscntrl(input[i]))
        {
            string[j] = input[i];
            j++;
            i++;
        }

        // check buffer
        else if(isspace(input[i]) || iscntrl(input[i]))
        {
            if(string[0] != '\0')
            {
                result = checkString(string, 0);


                // errors are 0 - 5
                if(result == 0)
                {
                    printlexerror(0);
                    exit(1);
                }

                else if(result == 1)
                {
                    printlexerror(1);
                    exit(1);
                }

                else if(result == 2)
                {
                    printlexerror(2);
                    exit(1);
                }

                else if(result == 3)
                {
                    printlexerror(3);
                    exit(1);
                }

                else if(result == 4)
                {
                    printlexerror(4);
                    exit(1);
                }

                else if(result == 5)
                {
                    printlexerror(5);
                    exit(1);
                }

                else if(result == 8)
                {}

                i++;
            }

            else
                i++;

            for(int k = 0; k < 50; k++)
                string[k] = '\0';
            j = 0;
        }
    }

    input[inLen - 1] = '\0';

	if (printFlag)
		printtokens();

	// these last two lines are really important for the rest of the package to run
	list[lex_index].type = -1;
	return list;
}

int checkString(char* string, int i)
{
    int len = strlen(string);

    int symFlag = 0;
    int maxNumLen = 0;
    int maxLen = 0;

    // digit characters
    if(isdigit(string[i]))
    {
        int check = 0;
        maxNumLen += 1;

        for(i = 1; i < len; i++)
        {

            // if the max length of digits is greater than our cap, return error
            if(maxNumLen > MAX_NUMBER_LEN)
                return 2;

            // if the next character is a digit, continue
            else if(isdigit(string[i]))
                maxNumLen++;

            // if the last character if a symbol
            else if((i == len-1) && (string[i] == '.' || string[i] == ',' || string[i] == ';') && check == 0)
            {
                symFlag = 1;
                // atoi does not care about the special character
                int num = atoi(string);

                // we get the special character and store it for use
                char c = string[len - 1];

                // place the number inside the token table
                list[lex_index].value = num;
                list[lex_index].type = 30;
                lex_index++;

                // we get the symbols at the end of our string and place
                // them in the table
                if(c == ',')
                    list[lex_index].type = 25;

                else if(c == ';')
                    list[lex_index].type = 29;


                else if(c == '.')
                    list[lex_index].type = 27;

                lex_index++;
            }

            // if its not a char/digit, return error
            else if(!isalpha(string[i]) && !isdigit(string[i]))
            {
                check = 1;
                symFlag = 1;
                int contin = 0;
                int error = 1;
                int go = 0;

                maxNumLen = 0;

                char a[12] = {'\0'};
                for(int k = 0; k < i; k++)
                {
                    if(isdigit(string[k + (i - 1)]))
                    {
                        a[k] = string[k + (i - 1)];
                        go = 1;
                    }

                    else
                        break;
                }

                if(go)
                {
                    // grab the number that was before the symbol and add it to the table
                    int num = atoi(a);
                    list[lex_index].value = num;
                    list[lex_index].type = 30;
                    lex_index++;
                }

                char b;
                char c;

                // grab the symbols individually to check if they are correct symbols
                b = string[i];
                c = string[i+1];

                char d[2] = {0};
                d[0] = b;

                char e[3] = {0};
                e[0] = b;
                e[1] = c;

                // we check if the symbol is two characters and flag it if it is
                for(int k = 0; k < 31; k++)
                {
                    if(strcmp(e, resWords[k]) == 0)
                    {
                        error = 0;
                        contin = 1;
                        list[lex_index].type = k + 1;
                        lex_index++;
                        i++;
                        break;
                    }
                }

                // if the flag is false, we check the one character symbol
                if(contin == 0)
                {
                    for(int k = 0; k < 31; k++)
                    {
                        if(strcmp(d, resWords[k]) == 0)
                        {
                            error = 0;
                            list[lex_index].type = k + 1;
                            lex_index++;
                            break;
                        }
                    }
                }

                if(error)
                    return 4;

            }

            // if the next character is not a digit, return error
            else if(isalpha(string[i]))
                return 1;

        }

        if(symFlag == 0)
        {
            int num = atoi(string);
            list[lex_index].value = num;
            list[lex_index].type = 30;
            lex_index++;
        }

        return 8;
    }

    // alpha characters
    else if(isalpha(string[i]))
    {
        int check = 0;
        int resFlag = 0;
        maxLen += 1;

        for(i = 1; i < len; i++)
        {
            // if the max length of char is greater than our cap, return error
            if(maxLen > MAX_IDENT_LEN)
                return 3;

            // if the next character is a char/dig, continue
            else if(isalpha(string[i]) || isdigit(string[i]))
                maxLen++;

            else if((i == len-1) && (string[i] == '.' || string[i] == ',' || string[i] == ';') && check == 0)
            {
                symFlag = 1;
                char ident[12] = { '\0' };
                char c = string[len - 1];

                for(int i = 0; i < len - 1; i++)
                {
                    ident[i] = string[i];
                }

                for(int i = 0; i < 31; i++)
                {
                    if(strcmp(ident, resWords[i]) == 0)
                    {
                        resFlag = 1;
                        list[lex_index].type = i+1;
                        lex_index++;
                    }

                    else if(i == 30 && resFlag != 1)
                    {
                        strcpy(list[lex_index].name, ident);
                        list[lex_index].type = 28;
                        lex_index++;
                    }
                }

                // we get the symbols at the end of our string and place
                // them in the table
                if(c == ',')
                    list[lex_index].type = 25;

                else if(c == ';')
                    list[lex_index].type = 29;

                else if(c == '.')
                    list[lex_index].type = 27;

                lex_index++;
            }

            // if its not a char/digit, return error
            else if(!isalpha(string[i]) && !isdigit(string[i]))
            {
                check = 1;
                symFlag = 1;
                int reserved = 0;
                int contin = 0;
                int error = 1;
                int go = 0;
                maxLen = 0;

                char a[12] = {'\0'};
                for(int k = 0; k < i; k++)
                {
                    if(isalpha(string[k + (i - 1)]) || isdigit(string[k + (i -1 )]))
                    {
                        a[k] = string[k + (i - 1)];
                        go = 1;
                    }

                    else
                        break;
                }

                if(go)
                {
                     for(int k = 0; k < 31; k++)
                    {
                        if(strcmp(a, resWords[k]) == 0)
                        {
                            // grab the identifier that was before the symbol and add it to the table
                            reserved = 1;
                            list[lex_index].type = k + 1;
                            lex_index++;
                        }
                    }

                    if(reserved == 0)
                    {
                        strcpy(list[lex_index].name, a);
                        list[lex_index].type = 28;
                        lex_index++;
                    }
                }

                char b;
                char c;

                // grab the symbols individually to check if they are correct symbols
                b = string[i];
                c = string[i+1];

                char d[2] = {0};
                d[0] = b;

                char e[3] = {0};
                e[0] = b;
                e[1] = c;

                // we check if the symbol is two characters and flag it if it is
                for(int k = 0; k < 31; k++)
                {
                    if(strcmp(e, resWords[k]) == 0)
                    {
                        error = 0;
                        contin = 1;
                        list[lex_index].type = k + 1;
                        lex_index++;
                        i++;
                        break;
                    }
                }

                // if the flag is false, we check the one character symbol
                if(contin == 0)
                {
                    for(int k = 0; k < 31; k++)
                    {
                        if(strcmp(d, resWords[k]) == 0)
                        {
                            error = 0;
                            list[lex_index].type = k + 1;
                            lex_index++;
                            break;
                        }
                    }
                }

                if(error)
                    return 4;
            }

        }

        if(symFlag == 0)
        {
            int resFlag = 0;
            for(int k = 0; k < 31; k++)
            {
                if(strcmp(string, resWords[k]) == 0)
                {
                    resFlag = 1;
                    list[lex_index].type = k + 1;
                    lex_index++;
                    break;
                }
            }

            if(resFlag == 0)
            {
                strcpy(list[lex_index].name, string);
                list[lex_index].type = 28;
                lex_index++;
            }
        }

        // it's valid identifier
        return 8;
    }

    // special characters
    else
    {
        int symFlag = 0;

        for(i = 0; i < 31; i++)
        {
            if(strcmp(string, resWords[i]) == 0)
            {
                symFlag = 1;
                list[lex_index].type = i + 1;
                lex_index++;
                return 8;
            }

            else if(i == 30 && symFlag != 1)
                return 4;
        }
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
