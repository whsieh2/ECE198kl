#include <stdio.h>
 
float TermArctan( float x, float k );
float Arctan( float x, float n );
float factorial( float a );
float power ( float b, float ex );
 
int main(){
 
  float x;  float n;  float result;
  printf("input x and n:");
  scanf("%f %f", &x, &n);
  result = Arctan( x, n);
  printf("arctan(%f) = %f\n",x, result);
  return 0;
}
 
float Arctan( float x, float n ){
 
  float sum = 0.0;
 
  /* implement the Arctan computation using calls to TermArctan */
	
	for(;n>=0;n--){
		sum = sum + TermArctan(x,n);
	}
 
  return sum;
}
 
float TermArctan( float x, float k ){
 
  /* implement computation of the kth term using power and factorial functions */

	float p1;
	float p2;
	float p3;
	float p4;

	p1 = (power(2.0,2.0 * k)) * (power(factorial(k),2.0));
	p2 = (factorial(2.0 * k + 1.0));
	p3 = power(x, 2.0 * k + 1.0);
	p4 = power(1.0 + power(x,2.0), k + 1.0);

	printf("p1 = %f  p2 = %f p3 = %f p4 = %f kn = %f result = %f\n",p1,p2,p3,p4,k,(p1*p3)/(p2*p4));
	
	return (p1*p3)/(p2*p4);

 
}
 
float factorial( float a ){

  /* implement the factorial function here */

	float i,fact=1.0;
	for(i=a; i > 0; i--){
		fact = fact * i;
	}

	return fact;
}
 
float power ( float b, float ex ){

  /* implement the power function here */

	float power=1.0;
	for(;ex>0;ex--){
		power = power * b;
	}
	return power; 
}
