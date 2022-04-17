// Karlos Morales Ramos
// COP 3502
// 9/16/2021
// P2 - Tree House Walking

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct coord
{
    int x;
    int y;
}coord;

float distanceCalc(int treesTotal);
float perm(coord* coords, int treesTotal, int k, int* used, int i, int j);

int main(void)
{
    int testCases;
    int trees;
    int treesTotal;
    float distanceValue = 0;
    int pass = 1;

    scanf("%d", &testCases);

    // we want a while loop to have the user input a valid
    // number whenever they input an invalid number
    while(pass)
    {
        if(testCases >= 0 && testCases <= 25)
            pass = 0;

        else
            scanf("%d", &testCases);
    }
    pass = 1;

    for(int i = 0; i < testCases; i++)
    {
        scanf("%d", &trees);

        // we want a while loop to have the user input a valid
        // number whenever they input an invalid number
        while(pass)
        {
            if(trees >= 0 && trees <= 8)
                pass = 0;

            else
                scanf("%d", &trees);
        }

        // this will multiply trees times 2 to get the
        // total amount (2n)
        treesTotal = 2 * trees;

        // we call the distance function to begin calculating
        // the total distance and store it in its respecitve variable
        distanceValue = distanceCalc(treesTotal);

        printf("%.3f\n", distanceValue);

    }

    return 0;
}

float distanceCalc(int treesTotal)
{
    int x, y, pass = 1;
    float distanceCalulation = 0;
    int* permArray = NULL;
    int* used = NULL;

    // create a space for the struct
    coord* coords = calloc(treesTotal, sizeof(coord));

    // we create the space for the used array
    used = malloc(treesTotal*sizeof(int));

    for(int i = 0; i < treesTotal; i++)
    {
        scanf("%d%d", &x, &y);

        // we want a while loop to have the user input a valid
        // number whenever they input an invalid number
        while(pass)
        {
            if(x >= -10000 && x <= 10000 && y >= -10000 && y <= 10000)
                pass = 0;

            else
                scanf("%d%d", &x, &y);
        }

        coords[i].x = x;
        coords[i].y = y;
    }

    // we call the permutation function which will return
    // the result
    distanceCalulation = perm(coords, treesTotal, 0, used, 0, 0);

    // send the result back to main
    return distanceCalulation;
}

float perm(coord* coords, int treesTotal, int k, int* used, int i, int j)
{
    float result = 1000000;
    float currResult;
    float smallerResult;

    // when k equals the amount of pair of trees
    // we return 0
    if(k == treesTotal/2)
        return 0;

    // we do not want i to always be zero, so we create a new variable
    // that will store every the value of i every time we send firstIndex
    // through the permutations
    for(int firstIndex = i; firstIndex < treesTotal; firstIndex++)
    {
        // when used is 1, we want to continue to the next
        // iteration of the loop
        if(used[firstIndex] == 1)
            continue;

        // we want a second index which will be the first index plus
        // because we do not want to use the same pair as the first index
        for(int secIndex = firstIndex + 1; secIndex < treesTotal; secIndex++)
        {
            // we check if this coordinates are also used
            // if it is, we continue to the next iteration
            if(used[secIndex] == 1)
                continue;

            // we set used to both coordinates in different
            // indexes
            used[firstIndex] = 1;
            used[secIndex] = 1;

            // we calculate the distance of the coordinates (trees)
            currResult = (float) sqrt(pow(coords[firstIndex].x - coords[secIndex].x, 2) +\
                                      pow(coords[firstIndex].y - coords[secIndex].y, 2));

            // we will permutate and get a smaller value
            smallerResult = perm(coords, treesTotal, k+1, used, firstIndex, secIndex);

            // when permutation ends, we want to set those indexes to not used
            used[firstIndex] = 0;
            used[secIndex] = 0;

            // if the sum of currResult and smallerResult is less than
            // result then we have a new result
            if(smallerResult + currResult < result)
                result = smallerResult + currResult;
        }
    }

    return result;
}
