/*Karlos Morales, COP3223C, 0V07, Treasure Hunt, 12/1/2020*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defines
#define	 MAX 3
#define MAXCREW 4

// Structures
struct pirate {
	int dig;
	int carry;
};

struct map {
	int sand;
	int treasure;
};

// Function prototypes
void pirateStatsOne(struct pirate stats);
void pirateStats(struct pirate* stats);
void treasureIsland(struct map island[MAX][MAX]);
void treasureIslandOne(struct map island);
int checkMap(struct map island[MAX][MAX], int x, int y);
void mapUpdate(struct map island[MAX][MAX], struct pirate stats[MAXCREW],
	int x, int y, int k, int* curTreasure);
int mapClear(struct map island[MAX][MAX]);

int main()
{
	FILE* ifp;
	char filename[50];
	int hours = 8;
	int i, j; 
	struct map island[MAX][MAX];
	struct pirate stats[MAXCREW];
	int x, y, k = 0;
	int curTreasure = 0;

	// boolean
	int done = 0;

	// we open the file here
	printf("You have arrived at Treasure Island!\n");
	printf("What is the name of your map?\n");
	scanf("%s", filename);
	ifp = fopen(filename, "r");

	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
		{
			fscanf(ifp, "%d", &island[i][j].sand);
			fscanf(ifp, "%d", &island[i][j].treasure);
		}

	for (i = 0; i < MAXCREW; i++)
	{
		fscanf(ifp, "%d", &stats[i].dig);
		fscanf(ifp, "%d", &stats[i].carry);
	}

	// Close the file
	fclose(ifp);

	printf("\n");

	// while there is still time (hours), the user can utilize his crew
	// to dig and gather treasure

	while (hours != 0)
	{
		printf("You have %d hours left to dig up the treasure.\n\n", hours);

		// This will print the crew member's stats for the user to see
		pirateStats(stats);

		printf("\n");

		// This is going to move through every single crew member
		for (i = 0; i < MAXCREW; i++)
		{
			printf("Where would you like to send crew member %d?\n", i + 1);

			// This will print the map normally and updated
			treasureIsland(island);

			printf("\n");

			scanf("%d %d", &x, &y);

			// This will check any wrong inputs the user has made 
			// and not let the user go on if they have inputted something
			// incorrectly
			while (!checkMap(island, x - 1, y - 1))
			{
				printf("Where would you like to send crew member %d?\n", i + 1);
				scanf("%d %d", &x, &y);
			}
			
			// This will update the map and correctly substract the sand
			// and treasure the island has based on each crew members
			// carry and dig. K is going to be used as a variable to 
			// move the crew members array
			mapUpdate(island, stats, x, y, k, &curTreasure);
			
			// k is used as a variable that will be moved in mapUpdate
			// k will be moving through all the numbers that are stored
			// inside "pirate carry" and "pirate dig"
			// it will reset back to 0 once it reaches crew man 4
			k++;
			if (k == MAXCREW)
				k = 0;

			// This will constantly check if all the grid is 0
			// if it is, done will be 1 and the for loop will break
			if (mapClear(island) == 1)
			{
				done = 1;
				break;
			}
		}

		// If the user gets to steal all the treasure in the island,
		// He will be congratulated for getting all the treasure
		// and the while loop will break
		if (done != 0)
		{
			printf("All the pirate's treasure belongs to you now!\n\n");
			break;
		}

		else
			hours--;
	}
	
	// If the user did not get all the treasure in time,
	// They will be said that they didn't gather all the treasure
	// on time and the program will end
	if (hours == 0)
	{
		printf("\nYou are forced to evacuate the island.\
 You have claimed %d pieces of the pirate's treasure!\n\n", curTreasure);
	}

	return 0;
}

// Pre-Condition: Carry and Dig have been read from the file map
// Post-Condition: Print the first "Carry" and "Dig" numbers we have stored
void pirateStatsOne(struct pirate stats)
{
	// since the function is not pass by reference, we use dots (".")
	printf("%d\t %d\n", stats.dig, stats.carry);

	return;
}

// Pre-Condition: Carry and Dig have been read from the file map
// Post-Condition: Print every single "Carry" and "Dig" numbers we have stored
// wrapper function to call pirateStatsOne and use it how many times we want
// we use pointer in "pirate" because it is referencing a pass by value in
// "pirateStatsOne"; since it's not an array, we have to add the "*"
void pirateStats(struct pirate* stats)
{
	int i;

	printf("Crew\tDig\t Carry\n");
	for (i = 0; i < MAXCREW; i++)
	{
		printf("%d\t", i + 1);
		// we call the other function that has all the "carry" and "dig" numbers
		// already stored and use a pointer function to be able to see them
		pirateStatsOne(stats[i]);
	}

	return;
}

// Pre-Condition: Sand has been read from the file map
// Post-Condition: Print the map with the numbers we have stored

void treasureIslandOne(struct map island)
{
	if (island.treasure == 0)
		printf("-\t");
	
	else if (island.sand == 0)
		printf("%dT\t", island.treasure);

	else
		printf("%ds\t", island.sand);

	return;
}

// Pre-Conditions: Sand and Treasure have been read from file map
// Post-Conditions: We create a 3x3 board in which the amount of sand 
//					is told to the user
// We construct the function without "*" because arrays are already referenced
// and we do not want to de-reference it
// Wrapper function to call treasureIslandOne and use it how many times we want

void treasureIsland(struct map island[MAX][MAX])
{
	int i, j;

	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
		{
			treasureIslandOne(island[i][j]);

			if (j == MAX - 1)
				printf("\n");
		}

	return;
}

// Pre-Condition: User input x and y numbers; sand and treasure have
//                all been picked up
// Post-Condition: If user input is below 0 or above 3, it will return 0.
//                 If user inputs where there is no sand and no treasure,
//                 it will return 1 because we want hours to go by and
//				   crew member to increment.
int checkMap(struct map island[MAX][MAX], int x, int y)
{

	if (x < 0 || x >= MAX)
	{
		printf("\nSorry, that was not valid.\n");
		return 0;
	}
	if (y < 0 || y >= MAX)
	{
		printf("\nSorry, that was not valid.\n");
		return 0;
	}

	if (island[x][y].sand == 0 && island[x][y].treasure == 0)
	{
		printf("\nThis section has already been cleared.\n\n");
		return 1;
	}

	return 1;
}

// Pre-Condition: User input x and y; pirate stats from file; island grid
// Post-Condition: The location on the grid when the user inputs x and y;
//                 if the location is sand, dig will substract sand; if
//                 location is treasure, carry will substract treasure.
//                 we also add the treasure the user has gotten 
void mapUpdate(struct map island[MAX][MAX], struct pirate stats[MAXCREW], 
	int x, int y, int k, int* curTreasure)
{

	// if the location has "sand", "dig" will subtract from it
	if (island[x - 1][y - 1].sand > 0)
	{
		// this will update the location of "sand" the user wanted
		// and subtract "sand" with "dig"
		island[x - 1][y - 1].sand = island[x - 1][y - 1].sand - stats[k].dig;

		if (island[x - 1][y - 1].sand <= 0)
		{
			// we make sand to zero instead of having a negative
			// in case of bugs and to be used in other lines of code
			island[x - 1][y - 1].sand = 0;
			printf("\nYou have removed all the sand from this section!\n\n");
		}

		else if(island[x - 1][y - 1].sand > 0)
			printf("\nYou have removed some of the sand from this section.\n\n");
	}

	// if the location has "treasure", "carry" will subtract from it and 
	// "treasure" will be added to curTreasure
	else if (island[x - 1][y - 1].treasure > 0)
	{
		// if the result of "treasure" minus "carry" is less than or equal to 0
		// then curTreasure will add what is in treasure since we don't 
		// want negative numbers
		if (island[x - 1][y - 1].treasure - stats[k].carry <= 0)
			*curTreasure += island[x - 1][y - 1].treasure;

		// if the substraction of "treasure" and "carry" is more than 0 
		// then curTreasure will add "carry" since if we substract it then
		// we will be adding the remainder of "treasure" minus "carry".
		// since we know some "treasure" will remain, we just add what "carry" is
		else
		{
			*curTreasure += stats[k].carry;
		}

		// this will update the location of "treasure" the user wanted
		// and subtract "treasure" with "carry"
		island[x - 1][y - 1].treasure = island[x - 1][y - 1].treasure 
			- stats[k].carry;
		


		if (island[x - 1][y - 1].treasure <= 0)
		{
			// we make treasure to zero instead of having a negative
			// in case of bugs and to be used in other lines of code
			island[x - 1][y - 1].treasure = 0;
			printf("\nYou take all the treasure back to the ship!\n\n");
		}

		else if (island[x - 1][y - 1].treasure > 0)
		{
			printf("\nYou take some of the treasure back to the ship.\n\n");
		}


	}

	return;
}

// Pre-Condition: none
// Post-Condition: If every single spot in the 3x3 grid, sand and treasure equal 0,
//                 clear will increment. If clear equals 9, then it will return 1.
int mapClear(struct map island[MAX][MAX])
{
	int i, j;
	int clear = 0;

	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			if (island[i][j].sand == 0 && island[i][j].treasure == 0)
				clear++;

	if (clear == 9)
		return 1;

	return 0;
}
