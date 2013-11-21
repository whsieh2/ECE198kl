#include "insertionSort.h"

node* insertionSort(node *head)
{
    node *sortedHead;
	node *unsortedHead;
	node *uscurrent;	//unsorted item
	node *scurrent;		//sorted item
	node *temp;			//temp node
	node *tempb;
	node *tempc;
	node *scurrentb;
	
	if (head == NULL)
		return;
	temp = head->next;
	tempc= head->next;
	while (temp !=NULL)
	{
		if (temp->value < tempc->value)
			tempb=temp;
		temp=temp->next;
			
	}		//finds the smallest number in the linked list
	unsortedHead = head;
	sortedHead = tempb->next;
	tempb->next = sortedHead->next;
	sortedHead->next=NULL;

	
	uscurrent = unsortedHead->next;
	sortedHead->next = NULL;
	scurrent = sortedHead->next;
	scurrentb=sortedHead->next;
	


	while (unsortedHead->next != NULL)
	{
		while (scurrent->value < uscurrent->value||sortedHead->next==NULL) //compared the values
		{
			scurrent = scurrent->next;
		}
		
		temp = scurrent->next;
		scurrent->next = uscurrent;
		unsortedHead->next = uscurrent-> next;
		uscurrent->next = temp;
		scurrent = sortedHead->next;		//clears the next pointer in the sorted list
	}
	return sortedHead;
}

void printList(node *head)
{
    node *current;
	node *previous;
	current = head->next;
	while (current != NULL)
	{
		printf("%d ", current->value);
		previous = current;
		current = current->next;
	}
}
