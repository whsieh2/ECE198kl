#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


void printtree_string(Node* node, int root)
{
	if(node == NULL)
		return;	
	if (node->left == NULL && node->right == NULL && !root)
		return;
	if (node->left == NULL && node->right == NULL && root)
	{
		printf(" %s -> \n", node->string);
		return;
	}
	if (node->left)
	{
		printf(" %s -> %s\n", node->string, node->left->string);
		printtree_string(node->left, 0);
	}
	else
		printf(" %s -> NULL\n", node->string);
	if (node->right)
	{
		printf(" %s -> %s\n", node->string, node->right->string);
		printtree_string(node->right, 0);
	}
	else
		printf(" %s -> NULL\n", node->string);
}

void insert_to_bst(Node **node, char *string)
{	

	//I am terribly sorry about the length of this function. Much of it is copy and pasted.
	//seg fault in this code. Unfortunately.
	//code goes here
	Node *current;
	current = *node;
	char first; //first letter of the node
	int i=0;
	while (string[i]!=' ')
		i++;
	int stringLength=i;
	char givenFirst = string[0];
	int givenASCII = givenFirst -'0';
	int givenIsCap =0; //If the given first char is cap=1, not=-1.

	if (givenASCII>=17&&givenASCII<=42)
		givenIsCap =1;
	else if (givenASCII>=49&&givenASCII<=74)
		givenIsCap =-1;
	else //not a letter, return
		return;

	int nodeASCII;
	int nodeIsCap =-1;


	while (current->left!=NULL||current->right!=NULL)
	{
		first = current->string[0];
		nodeASCII = first- '0';
		if (nodeASCII>=17&&nodeASCII<=42) //not right ranges
			nodeIsCap =1;
		else if (nodeASCII>=49&&nodeASCII<=74)
			nodeIsCap =-1;
		else
			return;

		if (givenIsCap>nodeIsCap)	//given is cap, but not node
		{	
			if (current->right!=NULL) //if the right child is not null, then current traverses
				current = current->right;
			else //the right child is null, so the new node gets created there.
			{
				Node* newNode = (Node*) malloc(sizeof(Node));
				current->right = newNode;
				for (i=0; i<stringLength;i++)
				{
					newNode->string[i]=string[i];
					return;
				}
			}
		}
		else if (givenIsCap<nodeIsCap) //given is not a cap, but node is.
		{
			if (current->left!=NULL) //if the left child is not null, then current traverses			
				current=current->left;
			else //the left child is null, so the new node gets created there.
			{
				Node* newNode = (Node*) malloc(sizeof(Node));
				current->left = newNode;
				for (i=0; i<stringLength;i++)
				{
					newNode->string[i]=string[i];
					return;
				}
			}
			
		}
		else if (givenIsCap==nodeIsCap) //both letters are of same kind
		{
			if (givenASCII > nodeASCII) //given is a bigger letter
		{	
			if (current->right!=NULL) //if the right child is not null, then current traverses
				current = current->right;
			else //the right child is null, so the new node gets created there.
			{
				Node* newNode = (Node*) malloc(sizeof(Node));
				current->right = newNode;
				for (i=0; i<stringLength;i++)
				{
					newNode->string[i]=string[i];
					return;
				}
			}
		}
			else if (givenASCII < nodeASCII) //node is bigger letter
		{
			if (current->left!=NULL) //if the left child is not null, then current traverses			
				current=current->left;
			else //the left child is null, so the new node gets created there.
			{
				Node* newNode = (Node*) malloc(sizeof(Node));
				current->left = newNode;
				for (i=0; i<stringLength;i++)
				{
					newNode->string[i]=string[i];
					return;
				}
			}
		}
			else 
				return printf("A string that starts with %c is already in the tree\n", givenFirst);

		}
		
	}
	
}

Node* lca(Node* node, char* p, char* q)
{
	int i=0;
	int areEqual=1; //see if the two strings are equal. 1 if they are, 0 if they aren't.
	while (p[i]!=' ' && q[i]!=' ')
	{
		i++;
		if (p[i]!=q[i])
		{
			areEqual=0;
		}
	}
	//code goes here    
	if (node ==NULL||areEqual==0)
		return node;
	else
	{
		if (lca(node->left, p,q)!=NULL && lca(node->right, p,q)!=NULL)
			return node;
		if (lca(node->left, p,q)==NULL)
			return node->right;
		if (lca(node->right, p,q)==NULL)
			return node->left;
		if (lca(node->left, p,q)==NULL&&lca(node->right, p,q)==NULL)
			return NULL;
	}
	
	
}



int main(int argc, char *argv[])
{
	int choice, input, ret;
	char n1[10];
	char n2[10];
	Node *root = NULL;
	char inputstring[10];

	while(1)
	{
		choice = 0;
		printf("------------------------------------\n");
		printf("Options\n");
		printf("1)Insert a string to tree (gold version)\n");
		printf("2)Insert a string to tree\n");
		printf("3)Display tree\n");
		printf("4)Find lowest common ancestor\n");
		printf("5)Exit\n");
		printf("------------------------------------\n");
		printf("Enter an option: ");
		ret = scanf("%d", &choice);
		if(ret == 0){
			printf("\nInvalid input. Aborting...\n");
			exit(-1);
		}

		switch(choice)
		{
			case 1:
					printf("Enter a string to add: ");
					scanf("%s", inputstring);
					insert_to_bst_gold(&root, inputstring);
					break;
			case 2:	
					printf("Enter a string to add: ");
					scanf("%s", inputstring);
					insert_to_bst(&root, inputstring);
					break;
			case 3:
					printf("\nTree-structure: \n");
					printtree_string(root, 1);
					printf("\n");
					break;
			case 4:
					printf("Enter the first string: ");
					scanf("%s", n1);
					printf("Enter the second string: ");
					scanf("%s", n2);
					Node* result = lca(root, n1, n2);
					if (result == NULL)
						printf("Did not find common ancestor!");
					else
					{
						printf("Their lowest common ancestor is: ");
						printf("%s\n", result->string);
					}
					break;
			case 5:
					exit(0);
			default:
					printf("Invalid choice. Try again\n");
		}
	}	

	return 0;
}
