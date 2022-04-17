// Karlos Morales Ramos
// COP 3502
// 9/28/2021
// P3 - Lottery

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
    int data;
    struct node* next;
}node;

typedef struct nodeList
{
    int nodeAmount;
    int skip;
    int threshold;
    node* LL;
}nodeList;

// functions to create lists and store lists inside an array
nodeList** readAllLists(int numGroups);
nodeList* readList(int pInGroup, int skipNum, int thresholdWinners);

// functions to delete loser nodes and to check the winner nodes in the
// lowest group
void remLosers(nodeList** list, int numGroups);
void checkWinner(nodeList** list, int numGroups);

// functions to add nodes to list and make the list circular
node* addNodes(node* list, int data);
node* makeCircular(node* list);

// functions to free the nodes of the list, the list and the
// array to hold the lists
void freeLists(nodeList** list, int numGroups);
void freeNodes(node* list);

int main(void)
{
    int pass = 1;

    int testCases;
    int numGroups;

    // initialize the pointer to linked lists
    nodeList** allLists = NULL;

    // we begin with the user input of testCases
    scanf("%d", &testCases);

    // we want a while loop to have the user input a valid
    // number whenever they input an invalid number
    while(pass)
    {
        if(testCases > 0 && testCases <= 25)
            pass = 0;

        else
            scanf("%d", &testCases);
    }
    pass = 1;


    for(int i = 0; i < testCases; i++)
    {
        // next we want the input of the number of groups we are going to be
        // working with
        scanf("%d", &numGroups);

        // we want a while loop to have the user input a valid
        // number whenever they input an invalid number
        while(pass)
        {
            if(numGroups > 0 && numGroups <= 10)
                pass = 0;

            else
                scanf("%d", &numGroups);
        }
        pass = 1;

        allLists = readAllLists(numGroups);

        remLosers(allLists, numGroups);

        checkWinner(allLists, numGroups);

        freeLists(allLists, numGroups);
    }

    return 0;
}

void checkWinner(nodeList** list, int numGroups)
{
    node* current = NULL;
    int lowNum = 1000000;
    int group;

    for(int i = 0; i < numGroups; i++)
    {
        current = list[i]->LL;

        while(current != NULL)
        {
            // if the current data is lower than the accumulated
            // lowNum, we reset group and lowNum with new values
            if(current->data < lowNum)
            {
                lowNum = current->data;
                group = i + 1;
            }
            current = current->next;
        }
    }

    printf("Lottery winner is person %d from group %d.\n", lowNum, group);
}

void remLosers(nodeList** list, int numGroups)
{
    int skip;
    int threshold;
    node* current = NULL;
    node* nextNode = NULL;
    node* temp = NULL;
    node* front = NULL;

    for(int i = 0; i < numGroups; i++)
    {
        // we get the data from the pointer array at i
        skip = list[i]->skip+1;
        threshold = list[i]->threshold;
        current = list[i]->LL;

        printf("Group #%d:\n", i+1);

        // will run until we have the amount of nodes same as threshold
        while(list[i]->nodeAmount != threshold)
        {
            // if skip is greater than 1
            if(skip > 1)
            {
                for(int j = 1; j < skip; j++)
                {
                    nextNode = current;
                    current = current->next;
                }

                temp = current;
                nextNode->next = temp->next;

                list[i]->nodeAmount--;
                printf("%d\n", current->data);

                current = nextNode->next;
                free(temp);
            }

            // if skip is 0
            else
            {
                temp = current;

                list[i]->nodeAmount--;
                printf("%d\n", current->data);

                current = current->next;
                free(temp);
            }
        }

        // if there's only one node inside the list, we make that the front
        // and the next equals to NULL
        if(list[i]->nodeAmount == 1)
        {
            front = current;
            front->next = NULL;
        }


        // create a tail node to know which is the higher value
        // and make the list linear
        node* tail = NULL;
        int doOnce = 0;

        // make the list non circular
        while(current->next != NULL)
        {
            // if current data is greater than the next data
            if(current->data > current->next->data)
            {
                // front will be that lowest data
                front = current->next;

                // tail will be that largest data
                tail = current;

                doOnce++;
            }

            current = current->next;

            // make sure that we make the tail->next NULL
            // once we find that, that number is the highest number
            if(doOnce)
            {
                // we make tail next equal NULL
                tail->next = NULL;
            }
        }

        // we store front back inside the list array
        list[i]->LL = front;
    }
}

nodeList* readList(int pInGroup, int skipNum, int thresholdWinners)
{
    nodeList* oneList = malloc(sizeof(nodeList));
    node* myList = NULL;
    int data;

    // this creates the values for the people inside
    // the lottery group
    for(int i = 1; i <= pInGroup; i++)
    {
        data = i;
        myList = addNodes(myList, data);
    }

    myList = makeCircular(myList);

    // stores the amount of people(amount of nodes) in the list
    oneList->nodeAmount = pInGroup;

    // stores the skip value
    oneList->skip = skipNum;

    // stores the winner threshold number
    oneList->threshold = thresholdWinners;

    // stores the list inside inside the space for lists
    oneList->LL = myList;

    return oneList;
}

nodeList** readAllLists(int numGroups)
{
    nodeList** lists = NULL;
    nodeList* singleList = NULL;
    int pass = 1;
    int limitPeople = pow(10,5);

    // these are the variables for the actions we are
    // going to take in the program
    int pInGroup;
    int skipNum;
    int thresholdWinners;

    lists = malloc(numGroups*sizeof(nodeList*));

    for(int i = 0; i < numGroups; i++)
        {
        // with the number of groups inputted, we want to use it to create
        // different groups with different amount of people
        scanf("%d", &pInGroup);

        // we want a while loop to have the user input a valid
        // number whenever they input an invalid number
        while(pass)
        {
            if(pInGroup >= 2 && pInGroup <= limitPeople)
                pass = 0;

            else
                scanf("%d", &pInGroup);
           }
        pass = 1;

        // we get the input for the skip number
        scanf("%d", &skipNum);

        // we want a while loop to have the user input a valid
        // number whenever they input an invalid number
        while(pass)
        {
            if(skipNum >= 0 && skipNum < pInGroup)
                pass = 0;

            else
                scanf("%d", &skipNum);
        }
        pass = 1;

        // we get the input for how many winners per group there can be
        scanf("%d", &thresholdWinners);

        // we want a while loop to have the user input a valid
        // number whenever they input an invalid number
        while(pass)
        {
            if(thresholdWinners >= 1 && thresholdWinners < pInGroup)
                pass = 0;

            else
                scanf("%d", &thresholdWinners);
        }
        pass = 1;

        lists[i] = malloc(sizeof(nodeList));

        singleList = readList(pInGroup, skipNum, thresholdWinners);

        lists[i] = singleList;
    }

    return lists;
}

node* addNodes(node* list, int data)
{
    node* current = NULL;

    // we create the first node pointing it to null
    // and pointing data to the data
    node* lotoList = malloc(sizeof(node));
    lotoList->data = data;
    lotoList->next = NULL;

    current = list;

    if(list == NULL)
        return lotoList;

    while(current->next != NULL)
        current = current->next;

    current->next = lotoList;

    return list;
}

node* makeCircular(node* list)
{
    node* current = NULL;
    node* front = NULL;

    if(list == NULL)
        return list;

    current = list;
    front = list;

    while(current->next != NULL)
        current = current->next;

    current->next = front;

    return front;
}

void freeLists(nodeList** list, int numGroups)
{
    for(int i = 0; i < numGroups; i++)
    {
        freeNodes(list[i]->LL);
        free(list[i]);
    }
    free(list);
}

void freeNodes(node* list)
{
    if(list == NULL)
        return;

    node* current = list->next;
    free(list);
    freeNodes(current);
}
