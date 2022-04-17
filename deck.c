// Karlos Morales Ramos
// 8/26/2021
// Program #0 - COP3502
// Check the longest ascending sequence of numbers
// and the longest sequence of suits in a deck

#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int NUMBERS = 52;
const int SUITS = 52;
const int NUMSUITS = 104;

int checkSameSuit(char suitLine[NUMSUITS]);
int checkLongestSeq(char numberLine[NUMSUITS]);

int main(void)
{
	int numCases, numberSeq, suitSeq;
    int pass = 1;

    scanf("%d", &numCases);

    while(pass)
    {

        if(numCases <= 25 && numCases > 0)
        {
            pass = 0;
        }

        else
        {
            scanf("%d", &numCases);
        }
    }

	for (int loop = 0; loop < numCases; loop++)
    {
        char line[NUMSUITS];
        scanf("%s", line);

        numberSeq = checkLongestSeq(line);
        suitSeq = checkSameSuit(line);

        printf("\n%d  %d\n", suitSeq, numberSeq);
    }

	return 0;
}


// Pre-condition: string array line is inputted
// Post-condition: we will pick the "number" characters in the line
//                 array and put them in another array.
//                 we will change the character array into
//                 a integer array with their respective value.
//                 numberSeq will increment when checking every
//                 value sequence until the end of the array
int checkLongestSeq(char numberLine[NUMSUITS])
{
    int numberSeq = 0, j = 0;
    char numberChar[NUMBERS];
    int numbers[NUMBERS];
    int currSeq = 0;

    for(int i = 0; i < NUMSUITS+1; i++)
    {
        // this will make every even number index which are the
        // numbers to be placed inside the new string array.
        // we increment j. we increment i twice to skip over the
        // "suit" index.
        if(i % 2 == 0)
        {
            numberChar[j] = numberLine[i];
            j++;
            i++;
        }
    }

    // we convert the characters to their individual value
    // and store it in an int array
    for(int i = 0; i < NUMBERS; i++)
    {


        if(numberChar[i] == '1')
        {
            int charValue = 1;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == '2')
        {
            int charValue = 2;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == '3')
        {
            int charValue = 3;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == '4')
        {
            int charValue = 4;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == '5')
        {
            int charValue = 5;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == '6')
        {
            int charValue = 6;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == '7')
        {
            int charValue = 7;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == '8')
        {
            int charValue = 8;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == '9')
        {
            int charValue = 9;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == 'T')
        {
            int charValue = 10;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == 'J')
        {
            int charValue = 11;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == 'Q')
        {
            int charValue = 12;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == 'K')
        {
            int charValue = 13;
            numbers[i] = charValue;
        }

        else if(numberChar[i] == 'A')
        {
            int charValue = 14;
            numbers[i] = charValue;
        }
    }

    // we will traverse the int array and check
    // the longest ascending sequence of numbers.
    // we will add 1 for every sequence
    // and only output the longest one
    for(int i = 0; i < NUMBERS; i++)
    {
        // when we have "ACE", which is going to be 14,
        // we go to the other statement
        if(numbers[i] == 14)
        {

            // if after the index of 14, we have an index
            // holding 2, then that is a sequence.
            // we add 1
            if(numbers[i+1] == 2)
            {
                currSeq++;
            }
        }

        // when the number is not 14..
        // if the number at [index] + 1 == the number at
        // the next index, we add 1 to the sequence
        else if(numbers[i]+1 == numbers[i+1])
        {
            currSeq++;
        }

        // if we do not have a 14 and a 2 after 14;
        // and the number at [index] + 1 does not
        // equal the number at the next index;
        // we get the current sequence, store it as the
        // longest sequence and reset current sequence
        else
        {
            if(currSeq > numberSeq)
            {
                numberSeq = currSeq;
            }
            currSeq = 0;
        }

    }

    // we add a "+1" because when we are comparing we leave
    // one behind
    return numberSeq+1;
}


// Pre-condition: string array line is inputted
// Post-condition: we will pick the "suit" characters in the line
//                 array and put them in another array.
//                 suitSeq will increment when checking every
//                 suit until the end of the array
int checkSameSuit(char suitLine[NUMSUITS])
{
    int suitSeq = 0, j = 0;
    char suits[SUITS];
    int currSeq = 0;

    for(int i = 0; i < NUMSUITS; i++)
    {
        // this will make every odd number index which are the
        // suits to be placed inside the new string array.
        // we increment j. we increment i twice to skip over the
        // "number" index.
        if(i % 2 == 1)
        {
            suits[j] = suitLine[i];
            j++;
            i++;
        }
    }

    // traverse the array suits and check how many times a character
    // is repeated, if one character is repeated more than the other
    // replace the count.
    // 52 (suits) - 1 = 51.. not looking at final character
    for(int i = 0; i < SUITS-1; i++)
    {
        // starts at 0 and looks at next character.. when at 51 it will look at 52
        if(suits[i] == suits[i+1])
        {
            currSeq++;
        }

        else
        {
            if(currSeq > suitSeq)
            {
                suitSeq = currSeq;
            }

            currSeq = 0;
        }
    }

    // we add a "+1" because when we are comparing we leave
    // one behind
    return suitSeq+1;
}

