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
    int val1;
    int val2;
    int i;

     for(i=0;i<=9;i++)
     { if(input[i]=='\0'){
       if(input[i]=='I'||input[i]=='X'||input[i]=='C'||input[i]=='M'||input[i]=='V'||input[i]=='L'||input[i]=='D')
       {
        if(input[i]=='I'){val1=1;}
        if(input[i]=='X'){val1=10;}
        if(input[i]=='C'){val1=100;}
        if(input[i]=='M'){val1=1000;}
        if(input[i]=='V'){val1=5;}
        if(input[i]=='L'){val1=50;}
        if(input[i]=='D'){val1=500;}

        if(input[i+1]==0){val2=0;}
        else
          {
        if(input[i+1]=='I'){val2=1;}
        if(input[i+1]=='X'){val2=10;}
        if(input[i+1]=='C'){val2=100;}
        if(input[i+1]=='M'){val2=1000;}
        if(input[i+1]=='V'){val2=5;}
        if(input[i+1]=='L'){val2=50;}
        if(input[i+1]=='D'){val2=500;}
          }

       if(val2<=val1){result=val1+result;}
       if(val2>val1){
       if(input[i]!='V')
         {result=result-val1;
          }
       else 
           {return -1;}
      }
        }
        else 
            return -1;}


     }
    return result;
}


