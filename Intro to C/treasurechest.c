/*Karlos Morales, COP3223C, 0V07, Treasure Chest, 10/29/2020*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main()
{
	FILE* ifp;
	char filename[50];
	int keyList[10];
	int n[10];
	int i, j, k = 0, l = 0, m = 0;
	int header = 7;
	char c;

	// booleans
	int done = 1;
	int check = 0;
	int regulate = 0;
	int wrongKey = 0;


	// we open the file here
	printf("What is the name of the file?\n");
	scanf("%s", filename);
	ifp = fopen(filename, "r");


	// We add the numbers inside the file onto an array.
	for (i = 0; i < header; i++)
		fscanf(ifp, "%d", &keyList[i]);


	printf("\n\n");

	printf("To get to me treasure you'll have to figure out which of me 100 \
keys are used in the 7 locks of me treasure chest.\n\n");


	// while loop to ask until the correct answer is given
	while (done != 0)
	{
		
		printf("Which keys will ye use?\n");
		for (i = 0; i < header; i++)
		{

			// We add user input numbers onto a second array and if user input is\
			not a number, then it will break loop
			if (scanf("%d", &n[i]) != 1)
			{

				// grab that inputted character and break the loop, the boolean\
				for error will come out
				c = getchar();
				regulate = 1;
				break;
			}


			// if user input is 0 or 100, the loop will stop ask for key numbers again
			if (n[i] == 0 || n[i] > 100)
			{
				printf("Only keys from 1 to 100, matey.\n\n");
				wrongKey = 1;
				break;
			}


			for (j = i - 1; j >= 0; j--)

				// checks if user input is the same as the one inputed before.\
				If it is the same, bool check will be true.
				if (n[i] == n[j])
					check = 1;
		}

		// we increment m when user input was not equal with the elements of\
		keyList array + if user input does not equal 0 + if user input is not\
		above 100
		for (i = 0; i < header; i++)
			

			// the reason for adding != 0 and < 101 was that the program would\
			still increment m when 0 and 101++ were inputted
			if (keyList[i] != n[i] && n[i] != 0 && n[i] < 101)
			{
				m++;
			}


		// when the element in array(keyList) is not the same as the element in\
		array(n) then this for loop breaks. But if the element is the same then\
		l increments
		for (i = 0; i < header; i++)
			if (keyList[i] != n[i])
				break;

			else
				l++;


		// keyList looks inside for every user input ( n[j] ) incrementally and if it\
		finds an element that keyList has, inside n[j], then K will increment. If not\
		it will continue looking (looping), until i = header
		for (i = 0; i < header; i++)
			for (j = 0; j < header; j++)
			{
				if (keyList[i] == n[j])
				{
					k++;
				}
			}



		// If bool check is true, the print will show and k will be 0.\
		If k IS NOT 0, then another print will appear which is not necessary.
		if (check != 0)
		{
			printf("You can only use each key once, matey!\n\n");
			k = 0;
		}


		// if user input equals a character, then this will prompt.
		if (regulate != 0)
		{
			printf("Error, enter numbers.\n\n");
			k = 0;
		}



		// we use this so that if the user inputs none of the keyList numbers\
		then the program will reply that all of them were wrong. we add the bool\
		so that when 2 "keys" are repeated, this print does not come out\
		same if user inputs a character. Also if there are no keys guessed
		if (m == 7 && check == 0 && regulate == 0 && k == 0)
			printf("Hah! None of those keys will work!\n\n");



		// when ALL the elements in the array(keyList) are equal in location and\
		equal elements as in the other array(n) then L will equal 7. If that happens\
		then the while loop finishes.
		if (l == 7)
			done = 0;



		// we use this to let the user know how many "keys" he got correct.\
		we ask a bool because we don't want the print to come out when\
		the while loop is finished and if the user did not input a character\
		and if the user did not put '0' or '101'
		if (k > 0 && done != 0 && regulate == 0 && wrongKey == 0)
		{
			printf("%d of those keys are correct, matey! \
But are they in the right order?\n\n", k);
		}



		// We equal to 0 these values for when the program does not end,\
		the values that were before get reset, even bools
		k = 0;
		m = 0;
		l = 0;
		

		// bools
		check = 0;
		regulate = 0;
		wrongKey = 0;
	}

	printf("Arr! You've opened me treasure chest and found...\n");
	printf("A map! To the rest of me treasure on Treasure Island.\n");
	printf("Hahaha!\n");


	fclose(ifp);

	system("pause");
	return 0;
}
