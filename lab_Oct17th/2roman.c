#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int convert(const char* input);
  
int main(){
    char input[11] = {};
    printf("Enter a Roman numeral number:");
    scanf("%10s", input);
    int decimal = 0;
    decimal = convert(input);
    if (decimal == -1)
    {
    printf("Invalid Input!\n");
    return 0;
    }
    else
    {
    printf("Decimal Number: %d\n", decimal);
    return 1;
    }
}
  
int convert(const char* input)
{
    int result = 0;
    int length = strlen(input);
    int i = 0;
    char char1; 
    char char2;
    int val1;
    int val2;
    int flag = 0;
    for (i = 0; i<length; i++)
    {
	char1 = input[i];
	char2 = input[i+1];
	if (char1 == 73){val1 = 1;}
	else if (char1 == 88){val1 = 10;}
	else if (char1 == 67){val1 = 100;}
	else if (char1 == 77){val1 = 1000;}
	else if (char1 == 86){val1 = 5;}
	else if (char1 == 76){val1 = 50;}
	else if (char1 == 68){val1 = 500;}   
        else {return -1;}
	if (i == length - 1)
 	{ val2 = 0;}
	else {
	if (char2 == 73){val2 = 1;}   
	else if (char2 == 88){val2 = 10;}   
	else if (char2 == 67){val2 = 100;}   
	else if (char2 == 77){val2 = 1000;}   
	else if (char2 == 86){val2 = 5;}   
	else if (char2 == 76){val2 = 50;}   
	else if (char2 == 68){val2 = 500;}   
	else {return -1;}
	}
	if (val2 <= val1)
	{
		result += val1;
		if (flag == 1) {flag = 0;}
	}
	else if (val2 > val1 && val1 != 5) 
	{
		if (flag == 0) {
		result -= val1;
		flag = 1;	
		}
		else {return -1;}
	} 
	else 
	{
		return -1;
	}

    }
    /*Implement your code here*/
    return result;
}
