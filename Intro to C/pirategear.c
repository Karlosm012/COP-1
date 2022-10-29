/*Karlos Morales, COP3223C, 0V07, Pirate gear, 9/19/2020*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

//We define the cost of new gear and used gear because they won't change
#define NEW_GEAR 15
#define USED_GEAR 5

int main()
{
	//Input values are all integers
	int ans;
	int numNewGear = 0;
	int numUsedGear = 0;
	int newNumNewGear = 0;
	int newNumUsedGear = 0;

	//average cost is a float because we want 2 decimal places after
	int newGeartotal = 0;
	int usedGearTotal = 0;
	int total;
	float averageGearCost;

	//This is the start of the program where we ask the user his input
	printf("Welcome to the market!\n");
	printf("What would you like to do?\n");
	printf("\t1. Buy New Gear.\n");
	printf("\t2. Buy Used Gear.\n");
	printf("\t3. Quit\n");

	scanf("%d", &ans);

	//We use a switch statement because it will make the code look much more cleaner\
	than a lot of if statements because then we have to repeat the start of the program\
	line.
	while (ans != 3)
	{
		switch (ans)
		{
		case 1:
			printf("How many pieces of new gear would you like to buy?\n");
			scanf("%d", &numNewGear);
			newGeartotal = numNewGear * NEW_GEAR;
			newNumNewGear += numNewGear;
			break;

		case 2:

			printf("How many pieces of used gear would you like to buy?\n");
			scanf("%d", &numUsedGear);
			usedGearTotal = numUsedGear * USED_GEAR;
			newNumUsedGear += numUsedGear;
			break;

		case 3:
			break;

		default:
			printf("Sorry, %d is not a valid option.\n", ans);
		}

		//We repeat the start of the program line for new user input.
		printf("What would you like to do?\n");
		printf("\t1. Buy New Gear.\n");
		printf("\t2. Buy Used Gear.\n");
		printf("\t3. Quit\n");

		scanf("%d", &ans);
	}
	

	total = newGeartotal + usedGearTotal;

	//We use an if statement for when the user does not buy any amount of gear\
	the reason for this is because the program will bug if an integer is divided by 0.
	if (total == 0)
	{
		printf("Your total cost is %d gold pieces.\n", total);
		printf("You obtained %d pieces of new gear and %d pieces of \
used gear.\n", newNumNewGear, newNumUsedGear);
	}

	//We use else to complete the program normally without any 0 bugs.
	else
	{
		printf("Your total cost is %d gold pieces.\n", total);
		printf("You obtained %d pieces of new gear and %d pieces of \
used gear.\n", newNumNewGear, newNumUsedGear);

		//We use a cast on total so the integer becomes a float and we get the average.
		averageGearCost = (float) total / (numUsedGear + numNewGear);
		printf("The cost per piece of gear is %.2f pieces of gold.\n", averageGearCost);
	}

	system("pause");
	return 0;
}