// Karlos Morales Ramos
// COP 3502
// 9/10/2021
// P1 - Smoothie


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_STRING_LENGTH 20

typedef struct item
{
    int itemID;
    int numParts;
}item;

typedef struct recipe
{
    int numItems;
    item* itemList;
    int totalParts;
}recipe;

char** readIngredients(int numIngredients);
recipe* readRecipe(int numItems);
recipe** readAllRecipes(int numRecipes);
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients);
void printOrder(char** ingredientNames, double* orderList, int numIngredients);
void freeIngredients(char** ingredientList, int numIngredients);
void freeRecipes(recipe** allRecipes, int numRecipes);

int main(void)
{
    int limit = pow(10,5);
    char** readIngredientsP = NULL;
    recipe** readAllRecipesP = NULL;
    double* calculateOrderP = NULL;
    int numIngredients;
    int numRecipes;
    int numStores;
    int numSmoothies;
    int pass = 1;


    scanf("%d", &numIngredients);

    // create this while loop so that when the correct answer
    // is not inputted(outside limit), we ask again
    while(pass)
    {
        if(numIngredients <= limit)
            pass = 0;

        else
            scanf("%d", &numIngredients);
    }
    pass = 1;

    // we will call the function that reads in the ingredients
    // based on how many ingredients the user is going to input
    readIngredientsP = readIngredients(numIngredients);

    scanf("%d", &numRecipes);

    // create this while loop so that when the correct answer
    // is not inputted (outside limit), we ask again
    while(pass)
    {
        if(numRecipes <= limit)
            pass = 0;

        else
            scanf("%d", &numRecipes);
    }
    pass = 1;

    // call readAllRecipes depending on how many recipes
    // we will create
    readAllRecipesP = readAllRecipes(numRecipes);

    scanf("%d", &numStores);

    // create this while loop so that when the correct answer
    // is not inputted (outside limit), we ask again
    while(pass)
    {
        if(numStores >= 1 && numStores<= 100)
            pass = 0;

        else
            scanf("%d", &numStores);
    }
    pass = 1;

    for(int i = 0; i < numStores; i++)
    {
        scanf("%d", &numSmoothies);

        while(pass)
        {
            if(numSmoothies > 0 && numSmoothies <= limit)
                pass = 0;

            else
                scanf("%d", &numSmoothies);
        }

        // we are going to calculate the order by sending how many smoothies
        // we want, sending all the recipes we created and the number of
        // ingredients we want
        calculateOrderP = calculateOrder(numSmoothies, readAllRecipesP, numIngredients);

        printf("Store #%d: \n", i+1);

        // output a list in order of each ingredient and the amount of
        // that ingredient (in pounds) rounded to 6 decimals
        printOrder(readIngredientsP, calculateOrderP, numIngredients);
    }

    freeIngredients(readIngredientsP, numIngredients);

    freeRecipes(readAllRecipesP, numRecipes);

    return 0;
}

// Pre-condition: 0 < numIngredients <= 100000
// Post-condition: Reads in numIngredients number of strings
//                 from standard input, allocates an array of
//                 strings to store the input, and sizes each
//                 individual string dynamically to be the
//                 proper size (string length plus 1), and
//                 returns a pointer to the array.
char** readIngredients(int numIngredients)
{
    char** readIngredientsP = NULL;
    char ingredients[MAX_STRING_LENGTH];

    // created the array of pointers
    readIngredientsP = malloc(numIngredients * sizeof(char*));

    for(int i = 0; i < numIngredients; i++)
    {
        // ask the user for the ingredients
        scanf("%s", ingredients);

        // created space based on the length of the ingredients
        // plus the null character
        readIngredientsP[i] = malloc((strlen(ingredients) + 1) * sizeof(char));

        // copied that ingredient inside the space
        strcpy(readIngredientsP[i], ingredients);
    }

    return readIngredientsP;
}

// Pre-condition: 0 < numItems <= 100
// Post-condition: Reads in numItems number of items
//                 from standard input for a smoothie recipe,
//                 Dynamically allocates space for a single
//                 recipe, dynamically allocates an array of
//                 item of the proper size, updates the
//                 numItems field of the struct, fills the
//                 array of items appropriately based on the
//                 input and returns a pointer to the struct
//                 dynamically allocated.
recipe* readRecipe(int numItems)
{
    // we create one space for one recipe
    recipe* smoothieRecipe = malloc(sizeof(recipe));

    // we create an array of items with the size of
    // how many items the user input
    item* itemList = calloc(numItems, sizeof(item));

    // we create this variable to store the sum of
    // all the units of ingredients the smoothie will use
    int sumTtlParts = 0;

    for(int i = 0; i < numItems; i++)
    {
        // we scan into the memory location
        // of both itemID and numParts, as i increments
        // we are placing more inputs in the other
        // array spaces of said variables
        scanf("%d", &itemList[i].itemID);
        scanf("%d", &itemList[i].numParts);

        // we store the sum of all numParts inside
        // an integer variable called sum total parts
        sumTtlParts += itemList[i].numParts;
    }

    // we point to the variable numItems and store
    // the number of items inside the struct of one recipe
    smoothieRecipe->numItems = numItems;

    // point to the pointer variable in recipe
    // "called" itemList and store the array in there
    smoothieRecipe->itemList = itemList;

    // we point to the variable totalParts and store
    // the total number of parts inside the struct of one recipe
    smoothieRecipe->totalParts = sumTtlParts;

    return smoothieRecipe;
}

// Pre-condition: 0 < numRecipes <= 100000
// Post-condition: Dynamically allocates an array of pointers to
//                 recipes of size numRecipes, reads numRecipes
//                 number of recipes from standard input, creates
//                 structs to store each recipe and has the
//                 pointers point to each struct, in the order
//                 the information was read in. (Should call
//                 readRecipe in a loop.)
recipe** readAllRecipes(int numRecipes)
{
    recipe** smoothieList = NULL;
    recipe* singleRecipe = NULL;
    int numItems;
    int pass = 1;

    // we create an array of pointers for the smoothie recipes
    smoothieList = malloc(numRecipes * sizeof(recipe*));

    for(int i = 0; i < numRecipes; i++)
    {
        scanf("%d", &numItems);

        // create this while loop so that when the correct answer
        // is not inputted(outside limit), we ask again
        while(pass)
        {
            if(numItems > 0 && numItems <= 100)
                pass = 0;

            else
                scanf("%d", &numItems);
        }

        // we create space for a single recipe in the array
        // of pointers
        smoothieList[i] = malloc(sizeof(recipe));

        // we read in that recipe from the function
        // that creates a single recipe per loop
        singleRecipe = readRecipe(numItems);

        // we store that single recipe inside the space for it
        // inside the array of pointers
        smoothieList[i] = singleRecipe;
    }

    // we return all the recipes back to main
    return smoothieList;
}

// Pre-condition: 0 < numSmoothies <= 100000, recipeList is
//                pointing to the list of all smoothie recipes and
//                numIngredients equals the number of total ingredients
// Post-condition: Reads in information from standard input about
//                 numSmoothies number of smoothie orders and dynamically
//                 allocates an array of doubles of size numIngredients such
//                 that index i stores the # of pounds of ingredient i
//                 needed to fulfill all smoothie orders and returns a
//                 pointer to the array
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients)
{
    double* amtOfEachItem = calloc(numIngredients, sizeof(double));

    recipe** recipeListOrder = recipeList;

    int smoothieRecipeIndex;
    int weightOfSmoothie;
    int pass = 1;
    int limit = pow(10, 5);

    // variable to hold the numbers we are going to use
    // to see the weight of the ingredients per smoothie ordered
    double divWeightTtlParts;
    double total;

    // we create a for loop that will each time we call this function
    // refresh the index we want of the recipe and the weight of the
    // new smoothie
    for(int i = 0; i < numSmoothies; i++)
    {

        scanf("%d", &smoothieRecipeIndex);

    // create this while loop so that when the correct answer
    // is not inputted (outside limit), we ask again
    while(pass)
    {
        if(smoothieRecipeIndex >= 0 && smoothieRecipeIndex <= limit)
            pass = 0;

        else
            scanf("%d", &smoothieRecipeIndex);
    }
    pass = 1;

    scanf("%d", &weightOfSmoothie);

    // create this while loop so that when the correct answer
    // is not inputted (outside limit), we ask again
    while(pass)
    {
        if(weightOfSmoothie > 0 && weightOfSmoothie <= 1000)
            pass = 0;

        else
            scanf("%d", &weightOfSmoothie);
    }

        // we do a second for loop to access every item inside the
        // recipe
        for(int j = 0; j < recipeListOrder[smoothieRecipeIndex]->numItems; j++)
        {

            // we divide the weight of the smoothie by the total parts of a recipe
            // to get the number we are going to multiply with every unit of the
            // smoothie ingredient
            // cast the integer from totalParts into a double
            divWeightTtlParts = (double)weightOfSmoothie/recipeListOrder[smoothieRecipeIndex]->totalParts;

            // we multiply the division with the unit of the smoothie ingredient of the recipe
            // cast the integer in numParts into a double
            total = divWeightTtlParts * (double)recipeListOrder[smoothieRecipeIndex]->itemList[j].numParts;

            // we create the frequency array here
            // the array will point to the recipe we want
            // then it will point to that array of items inside that recipe
            // and look at the variable itemID
            // the total of each multiplication will be added to the index
            // of that ingredient
            amtOfEachItem[recipeListOrder[smoothieRecipeIndex]->itemList[j].itemID] += total;
        }
    }

    // we return the frequency array with values
    return amtOfEachItem;
}


// Pre-condition: ingredientNames store the names of each
//                ingredient and orderList stores the amount
//                to order for each ingredient, and both arrays
//                are of size numIngredients
// Post-condition: Prints out a list, in ingredient order, of each
//                 ingredient, a space and the amount of that
//                 ingredient to order rounded to 6 decimal
//                 places. One ingredient per line.
void printOrder(char** ingredientNames, double* orderList, int numIngredients)
{
    for(int i = 0; i < numIngredients; i++)
    {
        // we want a value to be greater than 0 for it to print
        if(orderList[i] > 0)
            printf("%s %.6lf\n", ingredientNames[i], orderList[i]);
    }

    free(orderList);
}

// Pre-condition: ingredientList is an array of char* of size
//                numIngredients with each char* dynamically allocated
// Post-condition: all the memory pointed to by ingredientList is
//                 freed
void freeIngredients(char** ingredientList, int numIngredients)
{
    for(int i = 0; i < numIngredients; i++)
    {
        free(ingredientList[i]);
    }
    free(ingredientList);
}

// Pre-condition: allRecipes is an array of recipe* of size
//                numRecipes with each recipe* dynamically allocated
//                to point to a single recipe
// Post-condition: all the memory pointed to by allRecipes is freed
void freeRecipes(recipe** allRecipes, int numRecipes)
{
    for(int i = 0; i < numRecipes; i++)
    {
        free(allRecipes[i]->itemList);
        free(allRecipes[i]);
    }
    free(allRecipes);
}
