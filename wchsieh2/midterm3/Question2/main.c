#include "insertionSort.h"

int main()
{
    node *curr;
    node *head=NULL;
    int i;
    for(i=0;i<40;i++)
    {
        curr=(node *) malloc(sizeof(node));
        curr->value=rand()%100;
        curr->next=head;
        head=curr;
    }
    curr=head;
    printf("Unsorted List:\n");
    printList(curr);
    printf("\n");
    head=insertionSort(head);
    curr=head;
    printf("Sorted List:\n");
    printList(curr);
    printf("\n");
    
}

