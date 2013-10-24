
#include <stdio.h>
#define SIZE 10
 
int oddsum(int A[]);
 
int main()
{
    int i;
    int a[SIZE] = {1, 1,3, 4,5,6,7,8,9,0};
 
    int sum = oddsum(a);
  
    printf("%d\n",sum);
    return;
}
 
int oddsum(int ar[])
{
    int i;
    int sum = 0;
    for (i=0; i < SIZE; i++)
        if (ar[i]  & 1)
            sum += ar[i];
 
    return sum;
}
