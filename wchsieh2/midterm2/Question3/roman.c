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
    /*Implement your code here*/

	int i,count;
	char a[11];
	for (i=0;i<11;i++,input++){
		if(*input == '\0')
			break;
		a[i] = *input;
		if(a[i]=='I'||a[i]=='X'||a[i]=='C'||a[i]=='M'||a[i]=='V'||a[i]=='L'||a[i]=='D'){}
		else{
			return -1; // Type 1 error, input not any of the symbols.
		}
	}

	int val1;
	int val2;
	int t1,t2,t3;

	count=i;
	t3=0;
	for(i=0;i<count;i++){
		if(a[i]=='I')
			val1 = 1;
		else if(a[i]=='X')
			val1 = 10;
		else if(a[i]=='C')
			val1 = 100;
		else if(a[i]=='M')
			val1 = 1000;
		else if(a[i]=='V')
			val1 = 5;
		else if(a[i]=='L')
			val1 = 50;
		else if(a[i]=='D')
			val1 = 500;

		if(a[i+1]=='\0')
			val2=0;
		else if(a[i+1]=='I')
			val2 = 1;
		else if(a[i+1]=='X')
			val2 = 10;
		else if(a[i+1]=='C')
			val2 = 100;
		else if(a[i+1]=='M')
			val2 = 1000;
		else if(a[i+1]=='V')
			val2 = 5;
		else if(a[i+1]=='L')
			val2 = 50;
		else if(a[i+1]=='D')
			val2 = 500;

		if(val2<=val1){
			result = result + val1;
			t3=0; // Double subtraction will not occur as next value is smaller, so it resets.
		}
	
		if(val2>val1){
			if(t3==1){
				return -1;  // Type 3 error. Two characters already passed such that the two were I-Symbol, so they act as subtracting to third symbol.
			}
			for(t1=val1;t1>=10;){
				t1 = t1/10;
			}

			for(t2=val2;t2>=10;){
				t2 = t2/10;
			}

			if(t1==1 && t2==1)
				t3 = 1;

			if(t1==1){
				result = result - val1;
			}
			else{
				return -1; // Type 2 error, val2>val1 but current character is a V symbol.
			}
		}
	}
    return result;
}
