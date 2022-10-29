/*Karlos Morales, COP3223C, 0V07, Pirate crew Project!, 9/8/2020*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// We establish that the minimum required meters to be on the crew is 100 meters
#define SWIMMETERS 100

int main()
{
// we utilize two different character variables because question 2 has an if statement.
	int meters;
	char ask;
	char ask2;
	

	printf("Welcome, welcome! I will ask ye' two questions to know if ye' can be part of me crew.\n");

	printf("1. Do you like digging for treasure?\t(Y/N)\n");
	scanf_s(" %c", &ask);

// we ask this question with the different variable to be able to access the first if statement.
	printf("2. Are ye' able to swim?\t(Y/N)\n");
	scanf_s(" %c", &ask2);

// first if statement to ask how many meters the user can swim.
// we use || (or) so that if the user inputs the letters in lowercase or uppercase in whichever question, it does not
// bug the program
	if (ask2 == 'Y' || ask2 == 'y')
	{
		printf("How many meters can ye' swim?\n");
		scanf_s("%d", &meters);
	}

// second if statement to produce the results based on user input.
// we use || (or) so that if the user inputs the letters in lowercase or uppercase in whichever question, it does not
// bug the program
	if ((ask == 'Y' || ask == 'y') && (ask2 == 'Y' || ask2 == 'y') && (meters >= SWIMMETERS))
		printf("You may join me pirate crew! Arrrr ye' matey!\n");

	else 
		printf("You may not join me crew..\n");

	
	system("pause");
	return 0;
}