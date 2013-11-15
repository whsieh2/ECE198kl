#include<stdio.h>
#include<stdlib.h>
struct node
{
    struct node *next;
    int value;
};

typedef struct node node;

node* insertionSort(node *head);
void printList(node *head);

