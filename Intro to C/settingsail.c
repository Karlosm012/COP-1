/*Karlos Morales, COP3223C, 0V07, Setting Sail, 10/10/2020*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main()
{
	FILE* ifp;
	int i, j;
	int header;
	char filename[25];
	float n, max = 0, avg, sum = 0;
	int coldTemp = 0;
	int hotTemp = 0;

	//we add this float to keep track of the averages from all the temperatures\
	and specific months
	float highAverage[15];


	printf("Tell me about your crew's preferred temperature for sailing:\n");
	printf("What is the coldest temperature they can sail in?\n");
	scanf("%d", &coldTemp);

	if (coldTemp > 0 && coldTemp <= 80)
	{
		printf("What is the hottest temperature they can sail in?\n");
		scanf("%d", &hotTemp);
		if (hotTemp > coldTemp && hotTemp <= 120)
		{
			printf("Please enter the name of the weather data file:\n");
			scanf("%s", filename);
			ifp = fopen(filename, "r");

			printf("\n");

			//we begin our loop of months here
			for (i = 1; i < 12 + 1; i++)
			{
				//it will read the first number (header) and determine how\
				many other numbers (temps) that header has
				fscanf(ifp, "%d", &header);
				for (j = 0; j < header; j++)
				{
					//the other numbers in that specific header which are\
					the temperatures are stored in (n). The if statement will\
					utilize the numbers (n) that are in between the range of the\
					user's temperature
					fscanf(ifp, "%f", &n);
					if (n >= coldTemp && n <= hotTemp)
					{
						//after the if statement, sum is gonna add 1 for which temperature\
						managed to be in the range of the user's temperature then we divide\
						the sum by the number of temperatures (header) that were in that month and\
						get the percentage normally
						sum++;
						avg = (sum / (float)header) * 100;

						//we store the averages of the months inside highAverage to\
						utilize them for the highest average
						highAverage[i] = avg;
					}
					else if (sum == 0)
						avg = 0;
				}
				//we make sum 0 again so that it can read the quantity of numbers from the\
				if coldtemp && hottemp again with no sum of past months
				sum = 0.0;
				printf("Month %d: %.1f percent of days in range.\n", i, avg);

			}
			printf("\n");

			//In this loop, we are trying to get the highest number from all the\
			averages.
			max = highAverage[0];
			for (i = 1; i < 12 + 1; i++)
				if (highAverage[i] > max)
					max = highAverage[i];
			
			//In this for loop, max is already determined as the highest number\
			in whatever type of user input. We loop through all the averages\
			inside highAverage and the first average that is the same as max\
			gets outputted. We break the for loop when the if statement gets one.\
			This loop is important because if we do not use it the program will\
			output the second(third, etc.) highest number that happened first.
			for (i = 1; i < 12 + 1; i++)
				if (max == highAverage[i])
				{
					printf("You should leave for the Caribbean in month %d!\n", i);
					break;
				}

			

			//fclose goes here because it's in the same position as fopen\
			if not, we get an error.
			fclose(ifp);
		}

		//Else statements are meant to keep the temperatures true to\
		the program: cold below 80; hot above cold and below 120
		else
			printf("Not a correct temperature!\n");
	}
	else
		printf("Not a correct temperature!\n");

	return 0;
}