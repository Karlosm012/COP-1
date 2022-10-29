/*Karlos Morales, COP3223C, 0V07, Ocean Voyage, 11/10/2020*/

//Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constants for Arrays
#define STRLENGTH 30
#define NUMCREW 5
#define NUMSUPPLIES 4

//Constants for Distances (measured in miles)
#define CANARY 1261
#define GRENADA 3110
#define FINAL 500
#define DISTANCE 4871

//Function Signatures - do not change these
void setup(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int* captaintype, int* funds, int* distanceperday);
int countcrew(int crewstatus[NUMCREW]);
void printstatus(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW]);
void getsupplies(char supplytypes[NUMSUPPLIES][STRLENGTH], int supplies[NUMSUPPLIES], int* funds);
void dailyreport(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int supplies[NUMSUPPLIES], int funds, int traveled);
void rest(int supplies[NUMSUPPLIES], char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int* days);
int fish();
int Max(int a, int b);
int Min(int a, int b);
void event(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int* days, int supplies[NUMSUPPLIES]);

//Main function - This is the final version of main.  Any changes you make while
//creating the functions should be removed prior to submission.
int main()
{
    //crewnames and supplytypes are arrays of strings to store the names of the crew members
    //and the types of supplies that can be purchased and taken on the voyage
    char crewnames[NUMCREW][STRLENGTH];
    char supplytypes[NUMSUPPLIES][STRLENGTH] = { "Food", "Clothes", "Ship Parts", "Shovels" };
    //stop indicates whether or not the user would like to stop at a port
    //crewstatus indicates the status of each crew member, corresponding to the order of names
    //supplies has a total for each type of supply, corresponding to the order of supplies
    char stop;
    int crewstatus[NUMCREW], supplies[NUMSUPPLIES];
    //the distanceperday and funds depends on the captaintype the user selects
    //day is the current day, traveled is the total miles traveled, i is a loop counter
    //and action stores the intended action of the user for the day
    int distanceperday, captaintype, funds, traveled = 0, day = 1;
    int i, action;

    //seed the pseudorandom number generator
    srand(time(0));

    //initialize each variable with information from the user
    setup(crewnames, crewstatus, supplies, &captaintype, &funds, &distanceperday);

    //begin the game by purchasing initial supplies
    printf("\nBefore leaving Port Marin, you should purchase some supplies.\n");
    getsupplies(supplytypes, supplies, &funds);

    //continue the voyage until the ship reaches the intended destination
    //if all crew members perish, the journey cannot continue
    while (traveled < DISTANCE && countcrew(crewstatus) > 0) {
        printf("\n\n--It is day #%d.--\n", day);

        //check to see if the ship has reached the next port
        if(traveled >= (GRENADA+CANARY) && traveled < (GRENADA + CANARY + distanceperday) ) {
            printf("You have arrived at Grenada, at the edge of the Carribbean Sea.\n");
            printf("Would you like to make port? (Y/N)\n");
            scanf(" %c", &stop);

            if (stop == 'Y' || stop == 'y')
                getsupplies(supplytypes, supplies, &funds);

            traveled = (GRENADA+CANARY) + distanceperday;
        }
        else if (traveled >= CANARY && traveled < (CANARY + distanceperday) ) {
            printf("You have arrived at the Canary Islands.\n");
            printf("Would you like to make port? (Y/N)\n");
            scanf(" %c", &stop);

            if (stop == 'Y' || stop == 'y')
                getsupplies(supplytypes, supplies, &funds);

            traveled = CANARY + distanceperday;
        }
        //if between destinations: print the daily report and process the user's action for the day
        else {
            dailyreport(crewnames, crewstatus, supplies, funds, traveled);

            printf("\nWhat would you like to do?\n");
            printf("1 - Fish\n");
            printf("2 - Rest\n");
            printf("3 - Continue\n");
            scanf("%d", &action);

            if(action == 1) {
                supplies[0] += fish();
            }
            else if(action == 2) {
                day--;
                rest(supplies, crewnames, crewstatus, &day);
            }
            else {
                traveled += distanceperday;
                supplies[0] = Max(supplies[0] - countcrew(crewstatus) * 2, 0);
                event(crewnames, crewstatus, &day, supplies);
            }
        }
        day++;
    }

    printf("\n\n");

    //The final printout changes based on which condition broke the while loop
    if (countcrew(crewstatus) == 0) {
        printf("Your crew has perished in the search for treasure. :(\n");

        printstatus(crewnames, crewstatus);
    }
    else {
        printf("Your crew has made it safely to the island.\n");

        printstatus(crewnames, crewstatus);

        if(supplies[3] >= countcrew(crewstatus))
            printf("You have enough shovels to dig up the treasure!\n");
        else
            printf("Unfortunately, you will not be able to dig up the treasure.\n");
    }

    return 0;
}

//Pre-conditions:  none
//Post-conditions: each input parameter should be assigned an initial value

//What to do in this function: Provide the starting message for the user and ask how they plan to travel.
//  Based on their response initialize captaintype, funds, and distanceperday
//  -captaintype 1 should get 1000 funds and 80 distanceperday
//  -captaintype 2 should get 900 funds and 90 distanceperday
//  -captaintype 3 should get 800 funds and 100 distanceperday

//  Ask the user for their name.  Place this in the first row of crewnames, representing the captain.  Treat
//  crewnames as a 1-Dimensional array of strings. As an example: printf("%s", crewnames[0]); would print the
//  first string or the captains name to the screen.  Then ask for the names of the other 4 crew members in a loop.

//  Set the crew status to 2 for each crew member, representing healthy
//  Set the initial amount of supplies to be 0 for each supply
void setup(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW],
    int supplies[NUMSUPPLIES], int* captaintype, int* funds, int* distanceperday)
{
    int ans;
    int done = 1;
    int i;

    printf("You may now take your ship from Port Marin, Spain to the hidden\
 island in the caribbean on the old pirate's map.\n");

    printf("\nHow will you travel?\n");

    // This asks the user what type of captain he will be
    // It assigns them their respective money, distance per day
    // and type for the main function to recognize.
    // It will then assign them healthy status, and turns every supply
    // to 0
    while (done != 0)
    {
        printf("1. - As a merchant\n");
        printf("2. - As a privateer\n");
        printf("3. - As a pirate\n");
        scanf("%d", &ans);

        // Answer 1
        if (ans == 1)
        {
            *funds = 1000;
            *distanceperday = 80;
            *captaintype = 1;


            printf("\n");
            printf("As a Merchant, you begin your trip \
with %d gold pieces.\n", *funds);
            printf("You will be sailing your Carrack, with an \
average speed of %d miles per day.\n", *distanceperday);

            printf("\nWhat is your name, Captain?\n");
            scanf("%s", &crewnames[0]);

            printf("\n");
            printf("Who are the other members of your crew?\n");
            for (i = 1; i < NUMCREW; i++)
            {
                printf("%d: ", i);
                scanf("%s", &crewnames[i]);
            }

            for (i = 0; i < NUMCREW; i++)
                crewstatus[i] = 2;

            for (i = 0; i < NUMSUPPLIES; i++)
                supplies[i] = 0;

            done = 0;
        }

        // Answer 2
        else if (ans == 2)
        {
            *funds = 900;
            *distanceperday = 90;
            *captaintype = 2;


            printf("\n");
            printf("As a Privateer, you begin your trip \
with %d gold pieces.\n", *funds);
            printf("You will be sailing your Galleon, with an average \
speed of %d miles per day.\n", *distanceperday);

            printf("\nWhat is your name, Captain?\n");
            scanf("%s", &crewnames[0]);

            printf("\n");
            printf("Who are the other members of your crew?\n");
            for (i = 1; i < NUMCREW; i++)
            {
                printf("%d: ", i);
                scanf("%s", &crewnames[i]);
            }

            for (i = 0; i < NUMCREW; i++)
                crewstatus[i] = 2;

            for (i = 0; i < NUMSUPPLIES; i++)
                supplies[i] = 0;

            done = 0;
        }

        // Answer 3
        else if (ans == 3)
        {
            *funds = 800;
            *distanceperday = 100;
            *captaintype = 3;


            printf("\n");
            printf("As a Pirate, you begin your trip \
with %d gold pieces.\n", *funds);
            printf("You will be sailing your Clipper, with an average \
speed of %d miles per day.\n", *distanceperday);

            printf("\nWhat is your name, Captain?\n");
            scanf("%s", &crewnames[0]);

            printf("\n");
            printf("Who are the other members of your crew?\n");
            for (i = 1; i < NUMCREW; i++)
            {
                printf("%d: ", i);
                scanf("%s", &crewnames[i]);
            }

            for (i = 0; i < NUMCREW; i++)
                crewstatus[i] = 2;

            for (i = 0; i < NUMSUPPLIES; i++)
                supplies[i] = 0;

            done = 0;
        }
        
        // If the user enters numbers that aren't being asked
        // it will be an invalid response
        else
        {
            printf("\n");
            printf("That is not a valid response.\n");
        }
    }

    return;
}

//Pre-conditions:  crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//Post-conditions: returns the number of crew members that are alive

//What to do in this function: Traverse the crew status array and count how many crew members
//  have a status that is not 0.  Return this count.
int countcrew(int crewstatus[NUMCREW])
{
    int i;
    int alive = 0;

    // If the crewmember is healthy or ill, alive counter goes up.
    // if he is dead, the alive counter will not go up
    for (i = 0; i < NUMCREW; i++)
    {
        if (crewstatus[i] != 0)
            alive++;
    }

    // returns alive so that it can be used in substracting daily food.
    return alive;
}

//Pre-conditions:  crew names is an array of strings for the crew members
//                 crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//Post-conditions: none

//What to do in this function: print each crew members name and their status.
//  You may use a status array to shorten this process: char status[3][STRLENGTH] = {"Deceased", "Ill", "Healthy"};
void printstatus(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW])
{
    int i;

    // we use this array to mark each index (0 - 2): dead, ill, healthy
    char status[3][STRLENGTH] = { "Deceased", "Ill", "Healthy" };

    // we traverse every member of the crew to see if they have status index (0 - 2)
    // and update the status output accordingly
    for (i = 0; i < NUMCREW; i++)
    {
        if (crewstatus[i] == 2)
            printf("%s:  %s\n", crewnames[i], status[2]);
           
        else if (crewstatus[i] == 1)
            printf("%s:  %s\n", crewnames[i], status[1]);

        else if (crewstatus[i] == 0)
            printf("%s:  %s\n", crewnames[i], status[0]);

    }

    return;
}

//Pre-conditions:  supplytypes in an array of strings and gives the name of each supply type
//                 supplies is an array of integers representing how many of each type the crew has
//                 funds represents how many gold pieces the crew has to spend
//Post-conditions: the user may choose to buy supplies: incrementing values in supplies and
//                 decrementing funds

//What to do in this function: First print out the amount of gold the crew has.
//  Then print each supply type and the amount it costs.  You may use a cost array to shorten
//  this process: int supplycosts[NUMSUPPLIES] = {1, 2, 20, 10};
//  Based on the user's selection, ask the user how many of that supply they would like to buy.
//  Verify that the user has enough gold for their purchase and update the correct index of supplies.
//  Deduct the corresponding amount from the user's funds.
void getsupplies(char supplytypes[NUMSUPPLIES][STRLENGTH], 
    int supplies[NUMSUPPLIES], int* funds)
{
    int ans = 0;
    int food, clothes, shipParts, shovels;
    int supplycosts[NUMSUPPLIES] = { 1, 2, 20, 10 };

    // we loop the user buying items from port
    while (ans != 5)
    {
        printf("\n");
        printf("You have %d gold pieces.\n", *funds);
        printf("Available supplies:\n");
        printf("1.\tFood - 1 gold piece.\n");
        printf("2.\tClothes - 2 gold piece.\n");
        printf("3.\tShip Parts - 20 gold piece.\n");
        printf("4.\tShovels - 10 gold piece.\n");
        printf("5.\tLeave Store\n");
        scanf("%d", &ans);

        // If 1 the user is asked how much food he wants.
        if (ans == 1)
        {
            printf("\n");
            printf("How many pounds of food do you want to buy?\n");
            scanf("%d", &food);

            // supplycosts is the array holding what each supply costs
            food *= supplycosts[0];

            // If he doesnt have enough gold coins, this is the output
            if (*funds < food)
            {
                printf("Sorry, you cannot afford that much food.\n");
            }

            else
            {
                *funds -= food;
                supplies[0] += food;
            }
        }

        // If 2 the user is asked how many clothes he wants
        else if (ans == 2)
        {
            printf("\n");
            printf("How many sets of clothes do you want to buy?\n");
            scanf("%d", &clothes);

            clothes *= supplycosts[1];

            // If he doesnt have enough gold coins, this is the output
            if (*funds < clothes)
            {
                printf("Sorry, you cannot afford that many sets of clothes.");
            }

            else
            {
                *funds -= clothes;
                supplies[1] += clothes;
            }
        }

        // If 2 the user is asked how many extra ship parts he wants
        else if (ans == 3)
        {
            printf("\n");
            printf("How many extra ship parts do you want to buy?\n");
            scanf("%d", &shipParts);

            shipParts *= supplycosts[2];

            // If he doesnt have enough gold coins, this is the output
            if (*funds < shipParts)
            {
                printf("Sorry, you cannot afford that many ship parts.");
            }

            else
            {
                *funds -= shipParts;
                supplies[2] += shipParts;
            }
        }

        // If 2 the user is asked how many shovels he wants
        else if (ans == 4)
        {
            printf("\n");
            printf("How many shovels do you want to buy?\n");
            scanf("%d", &shovels);

            shovels *= supplycosts[3];

            // If he doesnt have enough gold coins, this is the output
            if (*funds < shovels)
            {
                printf("Sorry, you cannot afford that many shovels.");
            }

            else
            {
                *funds -= shovels;
                supplies[3] += shovels;
            }
        }

        else if (ans == 5)
            ;

        else
        {
            printf("\n");
            printf("Not a valid option.\n");
        }
    }

    return;
}

//Pre-conditions:  crew names is an array of strings for the crew members
//                 crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//                 supplies is an array of integers representing how many of each type the crew has
//                 funds represents how many gold pieces the crew has to spend
//                 traveled represents the total number of miles the ship has traveled from the beginning
//Post-conditions: none

//What to do in this function: Print a daily status report by telling the user how many miles have been
//  traveled.  Then, print the status of the crew by calling printstatus.  Print the funds and amount
//  of food that the ship has.  Then, let the user know how far they are from their next destination.
void dailyreport(char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], 
    int supplies[NUMSUPPLIES], int funds, int traveled)
{
    int destination;

    printf("You have traveled %d miles.\n", traveled);

    // prints the crewmates status(healthy, ill, dead)
    printstatus(crewnames, crewstatus);

    printf("\n");

    printf("You have %d gold pieces.\n", funds);


    if (supplies[0] > 0)
    {
        printf("You have %d pieces of food.\n", supplies[0]);
    }
   
    // if food is a negative number, this makes it 0
    else
    {
        supplies[0] = 0;
        printf("You have %d pieces of food.\n", supplies[0]);
    }


    // this marks the closest destination
    if (traveled < CANARY)
    {
        destination = CANARY - traveled;
        printf("You are %d miles from your next destination.\n", destination);
    }

    // marks the closest destination after Canary
    else if (traveled > CANARY && traveled < GRENADA + CANARY)
    {
        destination = GRENADA + CANARY - traveled;
        printf("You are %d miles from your next destination.\n", destination);
    }

    // marks the final destination
    else if (traveled > GRENADA && traveled < DISTANCE)
    {
        destination = DISTANCE - traveled;
        printf("You are %d miles from your next destination.\n", destination);
    }
    return;
}

//Pre-conditions:  a and b are both integers
//Post-conditions: the larger value will be returned
int Max(int a, int b)
{
    // I don't really understand why these functions are here
    // but this helps update food after a day has passed
    if (a > b)
        return a;

    else
        return b;
}

//Pre-conditions:  a and b are both integers
//Post-conditions: the smaller value will be returned
int Min(int a, int b)
{
    // This function is not used, but it would return the smaller value
    // if used
    
    if (a < b)
        return a;

    else
        return b;
}

//Pre-conditions:  supplies is an array of integers representing how many of each type the crew has
//                 crew names is an array of strings for the crew members
//                 crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//                 days represents the current day
//Post-conditions: the user will select a number of days to rest for. update days to reflect this number
//                 there is a small chance an ill crew member will recover during rest days

//What to do in this function: ask the user how many days they would like to rest for.
//  Updates days to indicate that that many days has now passed.  Deduct 2 pounds of food
//  for each crew member for each day rested.

//  Generate a pseudorandom value that will be either 0 or 1.  Generate a second value
//  between 0 and the number of original crew members.  If the first number is a 1,
//  the crew member in the index of the second number may recover if they are sick.
//  If they are healthy or deceased, nothing happens.  If the first number is a 0,
//  nothing happens.
void rest(int supplies[NUMSUPPLIES], 
    char crewnames[NUMCREW][STRLENGTH], int crewstatus[NUMCREW], int* days)
{
    int i;
    int daysRest;
    int coinFlip;
    int crewMember;

    srand(time(0));

    printf("\n");
    printf("How many days would you like to rest for?\n");
    scanf("%d", &daysRest);

    // Adds the amount of days rested to the day count
    *days += daysRest;

    // it substracts food according to members alive and days rested
    for (i = 0; i < NUMCREW; i++)
        if (crewstatus[i] != 0)
            supplies[0] -= daysRest * 2;

    // coinflip equals either 0 or 1
    coinFlip = rand() % 2;

    // crewmember points that which crew member is being affected
    crewMember = rand() % NUMCREW;

    // if coinflip equals 1 then the crew member that is ill (crewstatus[1])
    // is now healthy (crewstatus[2])
    if (coinFlip == 1)
        if (crewstatus[crewMember] == 1)
        {
            crewstatus[crewMember] = 2;

            // we use the same number "crewMember" to output his name
            printf("\n");
            printf("\n%s has recovered.\n", crewnames[crewMember]);
        }
    else
        ;

        return;
}

//Pre-conditions:  none
//Post-conditions: returns the number of pounds of fish gained by the ship

//What to do in this function: Generate a pseudorandom value between 0 and 3, inclusive.
//  Multiply this number by 50 and tell the user how many fish were caught.  Return
//  this value.
int fish()
{
    int fishing;
    int random;

    srand(time(0));

    // random number between 0 - 3, inclusive
    random = rand() % 4;

    fishing = random * 50;

    printf("\n-----\n");
    printf("Your crew lowers the nets and pulls up %d pounds of fish.\n", fishing);
    printf("-----\n");

    // returns the amount of random * 50
    return fishing;
}

//Pre-conditions:  crew names is an array of strings for the crew members
//                 crewstatus is an array of numerical indicators for the status of each crew member
//                 0 - deceased, 1 - ill, 2 - healthy
//                 days represents the current day
//                 supplies is an array of integers representing how many of each type the crew has
//Post-conditions: the status of a crew member or supplies may be affected by a random event,
//                 some events cause the ship to be delayed a certain number of days

//What to do in this function: Generate a pseudorandom number between 0 and 9, inclusive.  If the user
//  has run out of food, tell the user they have no food and increase your number by 2.  This number cannot
//  exceed 9.

//  Numbers 0, 1, and 2 do not correspond with any events.
//  Numbers 3 and 4 correspond with "positive events"
//      on a 3 the user will gain between 1 and 4 ship parts determined randomly
//      on a 4 the user will gain between 10 and 60 pounds of food determined randomly
//      both events take 1 day
//  Number 5 means the user will lose between 5 and 55 pounds of food
//      this event takes 1 day
//  Number 6 means the ship is stuck in fog, which takes 1 day
//  Number 7 means the ship is in a storm, which takes 2 days
//  Number 8 means something on the ship has broken
//      check the number of extra ship parts the crew has
//      if they have at least one ship part, they can replace it and continue
//      this takes 1 day
//      if they have no extra parts, they must stop and repair
//      this takes 3 days
//  Number 9 indicates sickness.  Generate a random number between 0 and the original
//      number of crew members.  Check the status of that crew member: if they are healthy,
//      they now fall ill.  If they are already ill, they now perish.  If they are already
//      deceased, nothing happens.

//  For any days spent in this way, deduct 2 pounds of food per crew member per day.
void event(char crewnames[NUMCREW][STRLENGTH], 
    int crewstatus[NUMCREW], int* days, int supplies[NUMSUPPLIES])
{
    int i;
    int random;
    int partGain, foodGain, foodLose, sickness;

    srand(time(0));

    // random number between 0 and 9, inclusive to begin any event
    random = rand() % 10;
 
    if (supplies[0] == 0)
    {
        printf("\n");
        printf("You have no food.\n");

        // this adds random 2 if the user has no food
        random += 2;

        // if random is above the limit which is 9, then we will substract
        // accordingly so that it is within the limit. 
        // 9 + 2 = 11, because 11 is out of bounds, we substract 2. 11 - 2 = 9
        // 9 is inside bounds
        if (random == 11)
            random -= 2;

        // 8 + 2 = 10, because 10 is out of bounds, we substract 1. 10 - 1 = 9
        // 9 is inside bounds
        // we could add randomness to the substracting in this one; could be fun,
        // but I will refrain from doing so
        else if (random == 10)
            random -= 1;

    }

    // from 0 - 2, nothing is going to happen
    if (random == 0)
        ;

    else if (random == 1)
        ;

    else if (random == 2)
        ;

    // 3 and 4 are good events
    else if (random == 3)
    {
        // we use a random number between 1 and 4 to give the user extra ship parts
        partGain = rand() % 4 + 1;

        printf("\n-----\n");
        printf("Another pirate ship pulls alongside and attacks!\n");
        printf("You fend them off and take %d extra ship parts.\n", partGain);
        printf("You spend the day recovering.\n");
        printf("-----\n");

        // supplies[2] is the ship parts index, we add the extra ship parts
        supplies[2] += partGain;
        *days += 1;

        // since they lost a day, you have to substract food usage
        for (i = 0; i < NUMCREW; i++)
            if (crewstatus[i] != 0)
                supplies[0] -= 1 * 2;
    }

    else if (random == 4)
    {
        // we use a random number between 10 and 60 to give the user extra food
        foodGain = rand() % 50 + 10;

        printf("\n-----\n");
        printf("Another pirate ship pulls alongside and attacks!\n");
        printf("You fend them off and take %d pounds of their food.\n", foodGain);
        printf("You spend the day recovering.\n");
        printf("-----\n");

        // supplies[0] is the food index, we add the random extra food
        supplies[0] += foodGain;
        *days += 1;

        // since they lost a day, you have to substract food usage
        for (i = 0; i < NUMCREW; i++)
            if (crewstatus[i] != 0)
                supplies[0] -= 1 * 2;
    }

    // 5 to 9 are the bad events
    else if (random == 5)
    {
        // we use are random number between 5 and 55 to substract the user's food
        foodLose = rand() % 50 + 5;

        printf("\n-----\n");
        printf("Another pirate ship pulls alongside and attacks!\n");
        printf("They took %d pounds of food and you spend the \
day recovering.\n", foodLose);
        printf("-----\n");

        // supplies[0] is the food index, we substract the random lost food
        supplies[0] -= foodLose;
        *days += 1;

        // since they lost a day, you have to substract food usage
        for (i = 0; i < NUMCREW; i++)
            if (crewstatus[i] != 0)
                supplies[0] -= 1 * 2;
    }


    else if (random == 6)
    {
        printf("\n-----\n");
        printf("Fog surrounds your ship. Drop anchor for one day.\n");
        printf("-----\n");

        *days += 1;

        // since they lost a day, you have to substract food usage
        for (i = 0; i < NUMCREW; i++)
            if (crewstatus[i] != 0)
                supplies[0] -= 1 * 2;
    }

    else if (random == 7)
    {
        printf("\n-----\n");
        printf("An ocean storm batters your ship. Drop anchor for two days.\n");
        printf("-----\n");

        // counter adds 2 days of the event
        *days += 2;

        // since they lost two days, you have to substract food usage
        for (i = 0; i < NUMCREW; i++)
            if (crewstatus[i] != 0)
                supplies[0] -= 2 * 2;
    }

    else if (random == 8)
    {
        printf("\n-----\n");
        printf("A part of your ship has broken!\n");

        if (supplies[2] > 0)
        {
            // we substract the used ship part from the supplies[2] (ship parts)
            // index
            supplies[2] -= 1;
            printf("You replace the broken part. It takes one day.\n");
            printf("-----\n");

            *days += 1;

            // since they lost a day, you have to substract food usage
            for (i = 0; i < NUMCREW; i++)
                if (crewstatus[i] != 0)
                    supplies[0] -= 1 * 2;
        }

        else
        {
            // since the user did not have an additional ship part, then
            // we add three days of punishment to the counter
            printf("You have no replacement parts. It takes three \
days to repair.\n");
            printf("-----\n");

            *days += 3;

            // since they lost three days, you have to substract food usage
            for (i = 0; i < NUMCREW; i++)
                if (crewstatus[i] != 0)
                    supplies[0] -= 3 * 2;
        }
    }

    else if (random == 9)
    {
        

        // random number (sickness) will become the crew member index
        sickness = rand() % NUMCREW;

        // if crew member was healthy(2), he will now be ill(1)
        if (crewstatus[sickness] == 2)
        {
            printf("\n-----\n");
            printf("%s has fallen ill.\n", crewnames[sickness]);
            printf("-----\n");
            crewstatus[sickness] = 1;
        }

        // if the crew member was ill(1), he is now dead(0)
        else if (crewstatus[sickness] == 1)
        {
            printf("\n-----\n");
            printf("%s has died.\n", crewnames[sickness]);
            printf("-----\n");
            crewstatus[sickness] = 0;
        }
    }

    return;
}