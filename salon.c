// Karlos Morales Ramos
// COP 3502
// 11/30/2021
// P6 - Salon

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SIZE 21
#define MAX 10

typedef struct customer
{
    char name[SIZE];
    char prefSty[SIZE];
    int loyaltyP;
    int salonTime;
    int hcMin;

    int finTime;

}customer;

typedef struct styArray
{
    char stylistName[SIZE];
    int capacity;
    customer** custList;

}styArray;

// functions
styArray* initHeap(int numSty);
styArray* insert(styArray* styList, customer* cust, int numSty, int numCust);
styArray rearrangeList(customer** custList, styArray styList, int numCust);

customer** bubbleSort(customer** cust, int numCust);
void swap(customer* a, customer* b);
void printList(styArray* styList, int numSty, int numCust);
void freeHeap(styArray* styList, int numSty, int numCust);

int main(void)
{
    int pass = 1;
    int customerLimit = pow(10,5);
    int numCustomers;
    int numStylists;

    scanf("%d %d", &numCustomers, &numStylists);

    while(pass)
    {
        if((numCustomers >= 0 && numCustomers <= customerLimit) &&
           (numStylists >= 0 && numStylists<= MAX))
            pass = 0;

        else
            scanf("%d %d", &numCustomers, &numStylists);
    }

    styArray* styList;

    styList = initHeap(numStylists);

    for(int i = 0; i < numStylists; i++)
    {
        char name[SIZE];
        scanf("%s", name);
        strcpy(styList[i].stylistName, name);
    }

    for(int i = 0; i < numCustomers; i++)
    {
        customer* cust = malloc(sizeof(customer));

        scanf("%d", &cust->salonTime);
        scanf("%s", cust->name);
        scanf("%s", cust->prefSty);
        scanf("%d", &cust->loyaltyP);
        scanf("%d", &cust->hcMin);

        // calls insert to place the first customer in the first array spot
        styList = insert(styList, cust, numStylists, numCustomers);
    }

    for(int i = 0; i < numStylists; i++)
    {
        if(styList[i].capacity > 2)
        {
            // rearrange in terms of loyalty points, priority queue
            styList[i] = rearrangeList(styList[i].custList, styList[i], styList[i].capacity);
        }

        for(int j = 2; j < numCustomers; j++)
            if(styList[i].custList[j] != NULL)
        {
            // if there was already someone getting the haircut, the next one in line finishes when the first person finishes
            // + they get their haircut
            if((styList[i].custList[j - 1]) != NULL)
            {
                styList[i].custList[j]->finTime = styList[i].custList[j - 1]->finTime +
                styList[i].custList[j]->hcMin;
            }
        }
    }

    // prints the output
    printList(styList, numStylists, numCustomers);

    // frees the heap and customer line
    freeHeap(styList, numStylists, numCustomers);

    return 0;
}

styArray* initHeap(int numSty)
{
    styArray* arrPtr = malloc(sizeof(styArray)*(numSty));

    for (int i = 0; i < numSty; i++)
    {
        arrPtr[i].custList = malloc(sizeof(customer*)*(MAX+1));
        arrPtr[i].capacity = 0;

        for(int j = 0; j < MAX+1; j++)
        {
            arrPtr[i].custList[j] = NULL;
        }
    }

    return arrPtr;
}

styArray* insert(styArray* styList, customer* cust, int numSty, int numCust)
{
    int min = 1000;
    int index;

    // double the array if the heap is full
    for(int i = 0; i < numSty; i++)
    {
        if(styList[i].capacity == MAX)
        {
            styList[i].custList = realloc(styList[i].custList, sizeof(styArray)*
                                          (2*styList[i].capacity+1));

            if(styList[i].custList = NULL)
                exit(0);

            styList[i].capacity *= 2;
        }

        if(strcmp(styList[i].stylistName, cust->prefSty) == 0)
        {
            styList[i].capacity++;
            styList[i].custList[styList[i].capacity] = cust;

            // store the value of haircut plus time they got in the salon
            styList[i].custList[styList[i].capacity]->finTime = styList[i].custList[styList[i].capacity]->hcMin +
            styList[i].custList[styList[i].capacity]->salonTime;



            return styList;
        }
    }

    // we check for the stylist with less customers and assign the new customer to them
    for(int i = 0; i < numSty; i++)
    {
        if(styList[i].capacity < min)
        {
            min = styList[i].capacity;
            index = i;
        }
    }
    styList[index].capacity++;
    styList[index].custList[styList[index].capacity] = cust;

    // change the name of the stylist because the one they input was not working
    // or they preferred none
    strcpy(styList[index].custList[styList[index].capacity]->prefSty, styList[index].stylistName);

     //store the value of haircut plus time they got in the salon
    styList[index].custList[styList[index].capacity]->finTime = styList[index].custList[styList[index].capacity]->hcMin +
    styList[index].custList[styList[index].capacity]->salonTime;

    return styList;
}

// rearranges the list in terms of loyalty points, if both customers asked for the same stylist
// and if one did and the other did not
styArray rearrangeList(customer** custList, styArray styList, int capacity)
{
    for(int i = 2; i < capacity; i++)
    {
        for(int j = 3; j <= capacity; j++)
        {
            // if first customer in line loyalty points are less than the next
            // swap them
            if(styList.custList[i]->loyaltyP < styList.custList[j]->loyaltyP)
            {
                swap(styList.custList[i], styList.custList[j]);
            }

            // if they are equal
            else if(styList.custList[i]->loyaltyP == styList.custList[j]->loyaltyP)
            {
                // check if they both asked for the same stylist
                if(strcmp(styList.custList[i]->prefSty, styList.stylistName) == 0 && strcmp(styList.custList[j]->prefSty, styList.stylistName) == 0)
                {
                    int res = strcmp(styList.custList[i]->name, styList.custList[j]->name);

                    if(res < 0)
                        swap(styList.custList[i], styList.custList[j]);
                }

                // check which one asked for the stylist
                else
                {
                    int res = strcmp(styList.custList[i]->prefSty, styList.stylistName);
                    int res1 = strcmp(styList.custList[j]->prefSty, styList.stylistName);

                    if(res1 == 0)
                    {
                        swap(styList.custList[i], styList.custList[j]);
                    }
                }
            }
        }
    }

    return styList;
}

void swap(customer* a, customer* b)
{
    customer temp = *a;
    *a = *b;
    *b = temp;
}

void printList(styArray* styList, int numSty, int numCust)
{
    printf("\n");

    // temp array to hold all the customers and print them out in order of finish time
    customer** custArray = malloc(sizeof(customer*)*numCust);
    int k = 0;

    for(int i = 0; i < numSty; i++)
    {
        for(int j = 1; j <= numCust; j++)
        {
            if(styList[i].custList[j] == NULL)
                break;

            // update the amount of loyalty points
            styList[i].custList[j]->loyaltyP = (styList[i].custList[j]->hcMin/10) +
            styList[i].custList[j]->loyaltyP;

            custArray[k] = styList[i].custList[j];
            k++;
        }
    }

    // use bubble sort to sort by finish time
    custArray = bubbleSort(custArray, numCust);

    for(int i = 0; i < numSty; i++)
    {
        for(int j = 1; j <= numCust; j++)
        {
            if(styList[i].custList[j] == NULL)
                break;

            printf("%s ", styList[i].custList[j]->name);
            printf("%d ", styList[i].custList[j]->finTime);
            printf("%d ", styList[i].custList[j]->loyaltyP);
            printf("%s \n", styList[i].custList[j]->prefSty);

        }
    }

    // free the temp array
    free(custArray);
}

customer** bubbleSort(customer** cust, int numCust)
{
    for(int i = numCust - 2; i >= 0; i--)
    {
        for(int j = 0; j <= i; j++)
        {
            if(cust[j]->finTime > cust[j+1]->finTime)
                swap(cust[j], cust[j+1]);
        }
    }

    return cust;
}

void freeHeap(styArray* styList, int numSty, int numCust)
{
    for(int i = 0; i < numSty; i++)
    {
        for(int j = 0; j < numCust; j++)
        {
            free(styList[i].custList[j]);
        }
        free(styList[i].custList);
    }

    free(styList);
}
