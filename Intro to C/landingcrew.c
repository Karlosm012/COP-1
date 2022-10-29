/*Karlos Morales, COP3223C, 0V07, Landing Crew, 9/25/2020*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main()
{
	//variables used for the program. i and k for 'for loops'; avgSum to add\
	avgTime input; totalTime to output the total avgTime
	int numberOfDays;
	int numberOfTrips;
	int i;
	int k;
	float avgTime;
	float avgSum = 0;
	float totalTime = 0;

	//We leave this outside because we don't want it repeating \
	numberOfDays input throughout the code
	printf("How many days will you observe the landing crew?\n");
	scanf("%d", &numberOfDays);

	//Our first 'for loop' asking for numberOfTrips input until it reaches the\
	numberOfDays user input
	for (i = 0; i < numberOfDays; i++)
	{
		printf("How many trips were completed in day #%d?\n", i + 1);
		scanf("%d", &numberOfTrips);

		//Second 'for loop' asking for the avgTime depening on user input of\
		numberOfTrips
		for (k = 0; k < numberOfTrips; k++)
		{
			printf("How long was trip #%d?\n", k + 1);
			scanf("%f", &avgTime);

			//we sum avgTime so that we can divide it by numberOfTrips and get\
			the Real avgTime that's totalTime
			avgSum += avgTime;
			totalTime = avgSum / numberOfTrips;
		}

		printf("Day #%d: The average time was %.3f.\n\n", numberOfDays, totalTime);

		//We HAVE to make avgSum equal 0 again because if not it will have a\
		number inside the code and subsequent answers will not be correct
		avgSum = 0;
	}


	system("pause");
	return 0;
}