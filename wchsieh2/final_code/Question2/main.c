#include <stdio.h>
#include <stdlib.h>

struct node_t {

  int num;
  struct node_t * next;

};

typedef struct node_t Node;

/* Given function */
void printList(Node* head);

/* Functions to implement */
Node* countRunLength(Node* node, int* len);
void removeNodes(Node* node, int numKeep, int numDel);
void insertNodes(Node* node, int numKeep, int numAdd);
void changeList(Node* head, int k);

int main(){

  printf("\n*** NOTE ***\nThe following tests are not comprehensive but are provided to give you a head start in your testing.\n");

  printf("\n\n\nTesting countRunLength:\n\n");

  Node* lHead;
  int len;

  Node* l1 = (Node*) malloc(sizeof(Node));
  Node* l2 = (Node*) malloc(sizeof(Node));
  Node* l3 = (Node*) malloc(sizeof(Node));
  Node* l4 = (Node*) malloc(sizeof(Node));

  l1->num = 1; l1->next = l2;
  l2->num = 1; l2->next = l3;
  l3->num = 1; l3->next = l4;
  l4->num = 2; l4->next = NULL;

  lHead = l1;
  lHead = countRunLength(lHead,&len);

  printf("Next Node's Expected Value:  2\n"); 
  printf("Next Node's Actual   Value:  %d\n",lHead->num); 
  printf("Expected Length: 3\n"); 
  printf("Actual   Length: %d\n",len); 


  printf("\n\n\nTesting removeNodes:\n\n");

  Node* rHead;

  Node* r1 = (Node*) malloc(sizeof(Node));
  Node* r2 = (Node*) malloc(sizeof(Node));
  Node* r3 = (Node*) malloc(sizeof(Node));
  Node* r4 = (Node*) malloc(sizeof(Node));

  r1->num = 1; r1->next = r2;
  r2->num = 1; r2->next = r3;
  r3->num = 1; r3->next = r4;
  r4->num = 1; r4->next = NULL;
  
  rHead = r1;
  removeNodes(rHead,3,1);

  printf("Expected List: 1 1 1\nActual list:   ");
  printList(r1);
  



  printf("\n\n\nTesting insertNodes:\n\n");

  Node* iHead;

  Node* i1 = (Node*) malloc(sizeof(Node));
  Node* i2 = (Node*) malloc(sizeof(Node));

  i1->num = 1; i1->next = i2;
  i2->num = 1; i2->next = NULL;
  
  iHead = i1;
  insertNodes(iHead,2,1);

  printf("Expected List: 1 1 1\nActual list:   ");
  printList(i1);
  



  printf("\n\n\nTesting changeList:\n\n");

  Node* head;

  Node* a1 = (Node*) malloc(sizeof(Node));
  Node* b1 = (Node*) malloc(sizeof(Node));
  Node* c1 = (Node*) malloc(sizeof(Node));
  Node* d1 = (Node*) malloc(sizeof(Node));
  Node* e1 = (Node*) malloc(sizeof(Node));
  Node* f1 = (Node*) malloc(sizeof(Node));

  a1->num = 1;
  b1->num = 1;
  c1->num = 3;
  d1->num = 5;
  e1->num = 5;
  f1->num = 6;
  
  a1->next = b1;
  b1->next = c1;
  c1->next = d1;
  d1->next = e1;
  e1->next = f1;
  f1->next = NULL;

  Node* a2 = (Node*) malloc(sizeof(Node));
  Node* b2 = (Node*) malloc(sizeof(Node));
  Node* c2 = (Node*) malloc(sizeof(Node));
  Node* d2 = (Node*) malloc(sizeof(Node));
  Node* e2 = (Node*) malloc(sizeof(Node));
  Node* f2 = (Node*) malloc(sizeof(Node));

  a2->num = 1;
  b2->num = 2;
  c2->num = 2;
  d2->num = 2;
  e2->num = 2;
  f2->num = 3;
  
  a2->next = b2;
  b2->next = c2;
  c2->next = d2;
  d2->next = e2;
  e2->next = f2;
  f2->next = NULL;



  head = a1;

  printf("Original List: ");
  printList(head);
  printf("Expected List: 1 1 1 3 3 3 5 5 5 6 6 6\n");
  changeList(head,3);
  printf("Your List:     ");
  printList(head);


  head = a2;

  printf("\nOriginal List: ");
  printList(head);
  printf("Expected List: 1 1 2 2 3 3\n");
  changeList(head,2);
  printf("Your List:     ");
  printList(head);
  printf("\n");

  return 0;

}

Node* countRunLength(Node* node, int* len){

  /* Insert your code here */
  if(node!=NULL){
    int a;
    a = node->num;
    *len = 1;
    node = node->next;
    for(;node!=NULL;){
      if(node->num==a){
        *len += 1;
      }
      else
        break;
      node = node->next;
    }
  }
  return node;


  /* Insert your code here 
     if( node->next ==NULL)
     return NULL;
     Node *current; //current node temp
     int count =1; //count
     int currentItem = node->num; //holds the value of the current node
     current = node->next; //current is now the next node
     while (currentItem != current->num)//when the next node is not equal to the value.
     {
     count++; //increment
     current = current->next; //traverse a node
     }
   *len = count; //*lens has the number of the name valued nodes
   if (count ==1)
   return NULL; //of it's only 1, return null.
   else
   return current->next; 
   */
}

void removeNodes(Node* node, int numKeep, int numDel){

  /* Insert your code here */
  Node *current;
  Node *currentNext;
  currentNext = node->next;
  int i;
  for (i=0; i<numKeep;i++)
  {
    current = currentNext;

  }
  for (i=0; i<numDel; i++)
  {
    currentNext = current->next;
    current->next = currentNext->next;
    currentNext->next = NULL;
    free(currentNext);		
  }

}

void insertNodes(Node* node, int numKeep, int numAdd){

  /* Insert your code here */
  Node *current;
  Node *currentNext;
  current = node;
  currentNext = current->next;

  int i;
  for(i=0;i<numKeep-1;i++)
  {
    current = current->next;
    currentNext= currentNext->next;
  }
  for(i=0;i<numAdd;i++)
  {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->num = node->num;
    current->next = newNode;
    newNode->next = currentNext;
    current = current->next;
  }


}
void changeList(Node* head, int k){ //unforunate seg fault beat me.

  /* Insert your code here */
  Node *current;
  current = head;
  int i;
  int numDel;
  int numAdd;
  int *len=0;

  current = head;
  while (countRunLength(current, len)!=NULL)
  {
    if (*len<k)
      removeNodes(current, k, *len-k);
    else if (*len>k)
      insertNodes(current, *len, k-*len);
    else
      current = countRunLength(current, len);
  }
}

void printList(Node* head){

  while(head != NULL){
    printf("%d ", head->num);
    head = head->next;
  }
  printf("\n");

}
