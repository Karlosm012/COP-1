/*Karlos Morales, COP3223C, 0V07, Pirate Project!, 9/4/2020*/

#include <stdio.h>
#include <math.h>

// Oranges is a constant since you will always need a crew to be able to sail otherwise the number will equal 0
#define SpainToCaribbean 7228
#define Oranges 0.5

int main()
{
	// TotalDays is a float because we want to ensure that TotalOranges is a real number
	int KilometerPerDay;
	int MaxCrewMembers;
	float TotalOranges;
	float TotalDays;

	printf("How many kilometers can you travel in a day?\n");
	scanf_s("%d", &KilometerPerDay);

	printf("How many crew members can your ship hold?\n");
	scanf_s("%d", &MaxCrewMembers);
	
	// Calculates how many days it will take him to reach the maximum Kilometers depending on kilometer per day
	// Use float casting to get a real number.
	TotalDays = (float) SpainToCaribbean / KilometerPerDay;
	
	TotalOranges = Oranges * MaxCrewMembers * TotalDays;
	printf("You will need %.2f oranges to make the trip.\n", TotalOranges);

	// The use of the real number and 1 decimal point facilitates if it's going to take half of the next day. 
	// Ex. 14.5 = 14 days and a half
	printf("It will take you %.1f days to get to the Caribbean!\nHave a safe trip!\n", TotalDays);

	system("pause");
	return 0;
}