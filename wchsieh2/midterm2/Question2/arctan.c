#include <stdio.h>
 
float TermArctan( float x, float k );
float Arctan( float x, float n );
float factorial(float fact );
float power ( float powBase, float powTop );
 
int main(){
 
  float x;  float n;  float result;
  printf("input x and n:");
  scanf("%f %f", &x, &n);
  result = Arctan(x,n);
  printf("arctan(%f) = %f\n",x, result);
  return 0;
}
 
float Arctan(float x, float n){
 
  float sum = TermArctan(x,0);
  float i;	

for ( i=1; i<n+1;i++)
	{
	sum = sum + TermArctan(x,i);	//Will add the sums of each TermArctan
	}
  return sum;

}
 
float TermArctan(float x, float k){

	float term1a;
	float term1b;
	float term1;
	float term2a;
	float term2b;
	float term2c;
	float term2;		//I split up each term so it'd be easier to organize

	term1a = (power(2,2*k))*(power(factorial(k),2));
	term1b = factorial(2*k+1);
	term1 = (term1a)/(term1b);	//Left side

	term2a = power(x, (2*k+1));
	term2b = (1 + power(x,2));
	term2c = power(term2b,(k+1));
	term2 = (term2a)/(term2c);	//Right side

	return ((term1a)*(term2a))/((term1b)*(term2c)); //The whole stuff
	
}
 
float factorial( float fact){
float i;
float factorialized = 1;
for (i=1; i < fact+1; i++)
	factorialized = factorialized * i;	//Will multiple each incremented i until the limit is reached.
return factorialized;
 
}
 
float power (float powBase, float powTop ){

	float powSoln = 1;
	float i;
	for (i = 0; i < powTop; i++)
		powSoln = powSoln * powBase; //Will multiple the base however many times that matches the top number.
	return powSoln;
 
}
