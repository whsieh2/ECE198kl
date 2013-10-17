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

    /*Implement your code here*/
    
     ssanf (input,"%10s", &input[]);

    int result = 0;
    int val0;
    int val1;
    int val2;
    int i;
    int test_input = 1;
    int count = 0;  /* the number of chars in the string */


    char current[i];
   
    /* read the input and store it to current */ 
    for (i = 0; i <= 9; i++ )
       {  
            
           
            if ( input [i] != 0)
           {
            if (input [i] = 73 ) {current [i] = 1; }
            if (input [i] = 88 ) {current [i] = 10; }
            if (input [i] = 67 ) {current [i] = 100; }
            if (input [i] = 77 ) {current [i] = 1000; }
            if (input [i] = 86 ) {current [i] = 5; }
            if (input [i] = 76 ) {current [i] = 50; }
            if (input [i] = 68 ) {current [i] = 500; }
            

            else {test_input = 0;}

            count = count + 1;
           }
           else break; 
            
       }
       
  

  /* the convert part */
               
         int j;
         for (j = 0; j < count; j++)
             {
                 if (j == (count - 1))
                 {    val0 = current [j - 1];
                      val1 = current [j];
                      val2 = 0;
                 }

                 else
                 {    val0 = current [j - 1];
                      val1 = current [j];
                      val2 = current [j + 1];
                 }
                 
                 int two_substract = 0; /* set a indicator for two consecutive substractions */

                 if (val0 << val1 << val2) two_substract = 1;
                 if (two_substract == 0; )                 
                 {
                    if (val2 <= val1) { result = result + val1;}
                    if ( (val2 > val1) && ( val1 != 5) && (val1 != 50) && (val1 != 500) ) {result = result - val1;}
                    else test_input = 0;
                 }
                  else test_input = 0;
             }


             if (test_input == 0) {result = -1;}
             else result = result;
       
            
     

   
    
   

 


    return result;
}
