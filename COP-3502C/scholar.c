// Karlos Morales Ramos
// COP 3502
// 10/26/2021
// P4 - Scholar

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

long long int* createList(int numBooks);
int isSorted(long long int* list, int low, int high);
void quicksort(long long int* list, int low, int high);
long long int partition(long long int* list, int low, int high);

int bookRead(long long int* list, int numBooks, int numPages);

void swap(long long int* a, long long int* b);
void printList(long long int* list, int numBooks);
void freeList(long long int* list);

int main(void)
{
    int testCases;
    int numBooks;
    int booksRead;
    long long int numPages;
    long long int* list;
    long long int pageLimit = pow(10, 14);
    int pass = 1;

    srand(time(0));

    scanf("%d", &testCases);

    // if the user inputs a number we do not want
    // we will ask them again
    while(pass)
    {
        if(testCases <= 25)
            pass = 0;

        else
            scanf("%d", &testCases);
    }
    pass = 1;

    for(int i = 0; i < testCases; i++)
    {
        scanf("%d", &numBooks);

        // if the user inputs a number we do not want
        // we will ask them again
        while(pass)
        {
            if(numBooks <= 100000)
                pass = 0;

            else
                scanf("%d", &numBooks);
        }
        pass = 1;

        scanf("%lld", &numPages);

        // if the user inputs a number we do not want
        // we will ask them again
        while(pass)
        {
            if(numPages <= pageLimit)
                pass = 0;

            else
                scanf("%lld", &numPages);
        }
        pass = 1;

        // create a list based on the number of books
        list = createList(numBooks);

        // sort the numbers the user is going to input
        // using quicksort
        quicksort(list, 0, numBooks-1);

        // send the list with the amount of books and the limit of pages
        // to read
        booksRead = bookRead(list, numBooks, numPages);

        // print booksRead
        printf("%d\n", booksRead);

        // free the list
        freeList(list);
    }

    return 0;
}

// here is where we count how many books are read depending on
// the number of pages
int bookRead(long long int* list, int numBooks, int numPages)
{
    long long int limiter = 0;
    int count = 0;

    for(int i = 0; i < numBooks; i++)
    {
        // adds the value in list to the limiter before count increments
        // because if it goes above the number of pages, we do not want
        // to add another book
        limiter += list[i];

        // if the addition of the books is less than or equal
        // to the number of pages, then count increments
        if(limiter <= numPages)
            count++;

        // else we break out
        else
            break;
    }

    // return how many books are read
    return count;
}

long long int* createList(int numBooks)
{
    long long int* list = malloc(numBooks * sizeof(long long int));
    long long int limit = pow(10, 9);
    long long int input;
    int i = 0;
    int pass = 1;

    while(i < numBooks)
    {
        scanf("%lld", &input);

        // if the user inputs a number we do not want
        // we will ask them again
        while(pass)
        {
            if(input > 0 && input <= limit)
            {
                list[i] = input;
                pass = 0;
            }

            else
                scanf("%lld", &input);
        }
        pass = 1;

        i++;
    }

    // returns an unsorted list of long long integers
    return list;
}

// checks if the list is sorted
int isSorted(long long int* list, int low, int high)
{
    // i less than or equal because if high equals 1
    // then 1 minus 1 equals 0 and the for loop will not
    // run leaving the array unsorted
    for(int i = low; i <= high - 1; i++)
    {
        if(list[i] > list[i+1])
        {
            return 0;
        }
    }

    return 1;
}

// we utilize quicksort to sort through the list, if it is
// sorted, then we return
void quicksort(long long int* list, int low, int high)
{

    if(isSorted(list, low, high))
        return;

    int split = partition(list, low, high);
    quicksort(list, low, split - 1);
    quicksort(list, split + 1, high);
}

// normal partition code utilizing the list of long long integers
long long int partition(long long int* list, int low, int high)
{

    int lowpos;
    int i;

    // we make the partition number random between low
    // and high so that we never get a worst case for n^2
    i = low + rand()%(high-low+1);

    // swap that random number with the number in low
    swap(&list[low], &list[i]);

    // this will be the partition variable
    lowpos = low;

    // we make low equal one more than the partition variable
    low++;

    while(low <= high)
    {
        while(low <= high && list[low] <= list[lowpos])
            low++;

        while(high >= low && list[high] > list[lowpos])
            high--;

        if(low < high)
            swap(&list[low], &list[high]);
    }

    swap(&list[lowpos], &list[high]);

    // returns the index where the partition is at
    return high;
}

void swap(long long int* a, long long int* b)
{
    long long int temp = *a;
    *a = *b;
    *b = temp;
}

void freeList(long long int* list)
{
    free(list);
}

void printList(long long int* list, int numBooks)
{
    for(int i = 0; i < numBooks; i++)
        printf("%lld ", list[i]);

    printf("\n");
}
