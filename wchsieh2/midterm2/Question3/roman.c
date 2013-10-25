#include <stdio.h>
#include <stdlib.h>
  
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
    int i;	
    int val1;
    int val2;
    int isNeg=0;	
    for (i=0; i < 11; i++)
    {
		if ((*(input + i)=='I')||(*(input + i)=='X')||(*(input + i)=='C')||(*(input + i)=='M')||(*(input + i)=='V')||(*(input + i)=='L')||(*(input + i)=='D')) //Will only execute if these characters are read
		{
			switch (*(input+i)) //Converts each letter to its corresponding numerical value.
			{
				case 'I':
					val1 = 1;
					break;
				case 'X':
					val1 = 10;
					break;
				case 'C':
					val1 = 100;
					break;
				case 'M':
					val1 = 1000;
					break;
				case 'V':
					val1 = 5;
					break;
				case 'L':
					val1 = 50;
					break;
				case 'D':
					val1 = 500;
					break;
	
			}
			if (*(input+i+1) =='\0') //If the next part is the end, then val2 =0
				val2=0;
			else
			{

				switch (*(input+i+1)) //Converts each next letter to its corresponding value. 
				{
					case 'I':
						val2 = 1;
						break;
					case 'X':
						val2 = 10;
						break;
					case 'C':
						val2 = 100;
						break;
					case 'M':
						val2 = 1000;
						break;
					case 'V':
						val2 = 5;
						break;
					case 'L':
						val2 = 50;
						break;
					case 'D':
						val2 = 500;
						break;
	
				}
			}
			if ( val2 <= val1) //Checkpoint 3
			{
				result += val1;
				isNeg = 1;	//whenever val1 is added, isNeg gets refreshed to it's value of 1
			}
			else if ((val2 > val1) && (*(input+i) != 'V')) //Checkpoint 4
			{
				result -=val1;
				isNeg--;
				if (isNeg == -1) //I use isNeg to see if val1 is subtracted twice, if it is subtracted twice in a row, 1 - 1 - 1= -1. It's checking for that.
					return -1;
			
			}
			else
				return -1; 
		
		}
		else if ((*(input+i)) == '\0') //If the currently read character is the end of the string, then we will return whatever value is in result.
			return result;
		else //One of the characters wasn't the correct roman numeral
			return -1;

    }	
    return result;
}
