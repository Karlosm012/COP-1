// Karlos Morales Ramos
// COP 3502
// 11/9/2021
// P5 - WordSort

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 21

typedef struct binTree
{
    char word[MAX];
    int freq;
    int height;
}binTree;

typedef struct treeNode
{
    binTree* node;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

// functions for the binary tree
treeNode* insert(treeNode* root, char word[], int depth);
void search(treeNode* root, char word[]);
int numNodes(treeNode* root);

// functions to create the array
void createArray(treeNode* root, binTree* arr, int i);
void mergeSort(binTree* arr, int start, int end);
void merge(binTree* arr, int start, int mid, int end);
void sortWords(binTree* arr, int maxNodes);

// print function
void printArray(binTree* arr, int maxNodes);

// free functions
treeNode* freeTree(treeNode* root);
binTree* freeArray(binTree* tree);

int main(void)
{
    int numWords;
    char word[MAX];
    int choice;

    int maxNodes;

    treeNode* myTree = NULL;
    binTree* arrTree = NULL;

    int pass = 1;

    scanf("%d", &numWords);

    while(pass)
    {
        if(numWords <= 200000)
            pass = 0;

        else
            scanf("%d", &numWords);
    }
    pass = 1;

    for(int i = 0; i < numWords; i++)
    {
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            scanf("%s", word);
            myTree = insert(myTree, word, 0);
            break;

        case 2:
            scanf("%s", word);
            search(myTree, word);
            break;
        }

    }

    // sums how many nodes are in the tree
    maxNodes = numNodes(myTree);

    // uses the sum of nodes to create a new array of structs
    arrTree = calloc(maxNodes, sizeof(binTree));
    createArray(myTree, arrTree, 0);

    // mergeSort function for the array of structs
    mergeSort(arrTree, 0, maxNodes - 1);

    // sort by frequency
    sortWords(arrTree, maxNodes);

    // prints the array
    printArray(arrTree, maxNodes);

    // frees the array and the binary tree
    freeTree(myTree);
    freeArray(arrTree);

    return 0;
}

treeNode* insert(treeNode* root, char word[], int depth)
{
    if(root == NULL)
    {
        treeNode* tmp = malloc(sizeof(treeNode));
        binTree* BT = malloc(sizeof(binTree));

        // create the struct storing the information
        BT->height = depth;
        BT->freq = 1;
        strcpy(BT->word, word);

        // create the nodes holding the struct
        tmp->node = BT;
        tmp->left = NULL;
        tmp->right = NULL;

        return tmp;
    }

    // stores the value of the strcmp
    int val = strcmp(word, root->node->word);

    if(val < 0)
    {
        depth++;
        root->left = insert(root->left, word, depth);
    }


    else if(val > 0)
    {
        depth++;
        root->right = insert(root->right, word, depth);
    }

    // if the word is the same, we increment the frequency
    else
        root->node->freq++;

    return root;
}

void search(treeNode* root, char word[])
{
    // if the word is not in the tree, we print -1 -1
    if(root == NULL)
    {
        printf("-1 -1\n");
        return;
    }

    int val = strcmp(word, root->node->word);

    if(val < 0)
        return search(root->left, word);

    else if(val > 0)
        return search(root->right, word);

    else
    {
        printf("%d %d\n", root->node->freq, root->node->height);
        return;
    }
}

int numNodes(treeNode* root)
{
    if(root == NULL)
        return 0;

    // recursively sum all the nodes
    return numNodes(root->left) + numNodes(root->right) + 1;
}

void createArray(treeNode* root, binTree* arr, int i)
{
    if(root == NULL)
        return;

    // if there is a number in index i, we keep incrementing i
    // to store in an empty spot
    while(arr[i].word != NULL & arr[i].freq != 0)
        i++;

    strcpy(arr[i].word, root->node->word);
    arr[i].freq = root->node->freq;
    i++;

    createArray(root->left, arr, i);
    createArray(root->right, arr, i);

    return;
}

void mergeSort(binTree* arr, int start, int end)
{
    int mid;

    if(start < end)
    {
        mid = (start + end) / 2;

        // sort bottom half
        mergeSort(arr, start, mid);

        // sort top half
        mergeSort(arr, mid + 1, end);

        // merge both halves
        merge(arr, start, mid + 1, end);
    }
}

void merge(binTree* arr, int start, int mid, int end)
{
    int count1, count2, newIndex;
    int length = end - start + 1;

    binTree* tmp = calloc(length, sizeof(binTree));

    count1 = start;
    count2 = mid;

    newIndex = 0;

    while((count1 < mid) || (count2 <= end))
    {

        // if the freq is greater or equal, greater so that it prints from highest
        // value to lowest and equal to check for words instead
        if(count2 > end || (count1 < mid && arr[count1].freq > arr[count2].freq))
        {
            tmp[newIndex] = arr[count1];
            count1++;
            newIndex++;
        }

        else if(count2 > end || (count1 < mid && arr[count1].freq == arr[count2].freq))
        {
            // if the frequencies are equal, check the words
            if(arr[count1].freq == arr[count2].freq)
            {
                // if the first word is greater than the second word
                if(strcmp(arr[count1].word, arr[count2].word) > 0)
                {
                    // we swap the structs
                    binTree temp = arr[count1];
                    arr[count1] = arr[count2];
                    arr[count2] = temp;
                }
            }

            // add the swapped node or the normal node into the temporary array
            tmp[newIndex] = arr[count1];
            count1++;
            newIndex++;
        }

        else
        {
            tmp[newIndex] = arr[count2];
            count2++;
            newIndex++;
        }
    }

    for(int i = start; i <= end; i++)
        arr[i] = tmp[i - start];

    free(tmp);
}

void sortWords(binTree* arr, int maxNodes)
{
    for(int i = 0; i < maxNodes; i++)
    {
        for(int j = 1; j < maxNodes; j++)
        {
            if(arr[i].freq == arr[j].freq)
            {
                if(strcmp(arr[i].word, arr[j].word) < 0)
                {
                    binTree temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
}

void printArray(binTree* arr, int maxNodes)
{
    for(int i = 0; i < maxNodes; i++)
    {
        printf("%s %d\n", arr[i].word, arr[i].freq);
    }
}

treeNode* freeTree(treeNode* root)
{
    if(root != NULL)
    {
        // recursively move until we hit a root
        freeTree(root->left);
        freeTree(root->right);

        // we free the BT node
        free(root->node);

        // free the tree node
        free(root);
    }
}

binTree* freeArray(binTree* tree)
{
    free(tree);
}
