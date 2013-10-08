#include <stdlib.h>
#include <stdio.h>

#include "lorenz.h"


/*
INTRO: My program will fscanf 9 values from the input file and stores these values are unique variables.
Then it will do a loop, until t_start reaches t_end's value by incrementing t_start by dt each loop.
I use the recursion formula given to implement the program inside the loop. Each loop will print x0, y0, and z0, on each 
line of the output file. For Rk4, I do the exact same thing, except I used a different given formula. 

*/

int do_lorenz_euler(const char *input_filename, const char *output_filename)
{
	FILE *input = fopen(input_filename, "r"); //input points to the inputted file name. Will read
	FILE *output = fopen(output_filename, "w+"); //output points to the output file name. Will write and create a new one.

	double x0 = 0; 
	double y0 = 0;
	double z0 = 0;
	double t_start = 0;
	double dt = 0;
	double t_end = 0;
	double sigma = 0;
	double rho = 0;
	double beta = 0;
	double x1 = 0;
	double y1 = 0;
	double z1 = 0;
	
	
	if( 9 == fscanf(input, "%lf %lf %lf %lf %lf %lf %lf %lf %lf" ,&x0, &y0, &z0, &t_start, &dt,
	&t_end, &sigma, &rho, &beta)) //If we only scanned 9 items from the input file. Each value is assigned to a variable.
	{
		while (t_start < t_end) //Loop will run until t_start is equall to t_end.
		{			
			
			fprintf(output, "%lf %lf %lf %lf\n", t_start, x0, y0, z0); //prints the current x0, y0, z0 values on the current line.
			x1 = x0 + sigma*(y0-x0)*dt; //given x0+1 equation
			y1 = y0 + (x0*(rho-z0)-y0)*dt; //given y0+1 equation
			z1 = z0 + (x0*y0-beta*z0)*dt; //given z0+1 equation
			
			t_start = t_start + dt; // increment t_start by dt
			
			x0=x1; //x0 is updated
			y0=y1; //y0 is updated
			z0=z1; //z0 is updated
	
		}
		fclose(input); //close the file
		fclose(output); //close the file
		 return 0; //returns 0 if the input file has 9 values.
    }
   else
   	return -1; //input file did not have 9 values.
}

int do_lorenz_rk4(const char *input_filename, const char *output_filename)
{
    FILE *input = fopen(input_filename, "r");
	FILE *output = fopen(output_filename, "w+");

	double x0;
	double y0;
	double z0;
	double t_start;
	double dt;
	double t_end;
	double sigma;
	double rho;
	double beta;
	double x1;
	double y1;
	double z1;
	
	double k1x;
	double k1y;
	double k1z;
	
	double k2x;
	double k2y;
	double k2z;
			
	double k3x;
	double k3y;
	double k3z;
			
	double k4x;			
	double k4y;
	double k4z;
	
	if( 9 == fscanf(input, "%lf %lf %lf %lf %lf %lf %lf %lf %lf" ,&x0, &y0, &z0, &t_start, &dt, //same as top
	&t_end, &sigma, &rho, &beta)) 
	{
		while (t_start < t_end)//same as top
		{			
			
			
			
			fprintf(output, "%lf %lf %lf %lf\n", t_start, x0, y0, z0);//same as top
			
			k1x = sigma*(y0-x0); //Given formula from the website.
			k1y = (x0*(rho-z0)-y0); //Given formula from the website.
			k1z = (x0*y0-beta*z0); //Given formula from the website.
			
			k2x = sigma*((y0+0.5*dt*k1y)-(x0+0.5*dt*k1x)); //Given formula from the website.
			k2y = ((x0+0.5*dt*k1x)*(rho-(z0+0.5*dt*k1z))-(y0+0.5*dt*k1y)); //Given formula from the website.
			k2z = ((x0+0.5*dt*k1x)*y0-beta*z0); //Given formula from the website.
			 
			k3x = sigma*((y0+0.5*dt*k2y)-(x0+0.5*dt*k2x));//Given formula from the website.
			k3y = ((x0+0.5*dt*k2x)*(rho-(z0+0.5*dt*k2z))-(y0+0.5*dt*k2y));//Given formula from the website.
			k3z = ((x0+0.5*dt*k2x)*(y0+0.5*dt*k2y)-beta*(z0+0.5*dt*k2z)); //Given formula from the website.
			
			k4x = sigma*((y0+dt*k3y)-(x0+dt*k3x));//Given formula from the website.
			k4y = ((x0+dt*k3x)*(rho-z0)-(y0+0.5*dt*k3y));//Given formula from the website.
			k4z = ((x0+dt*k3x)*(y0+dt*k3y)-beta*(z0+dt*k3z)); //Given formula from the website.
			
			x1 = (0.1666666)*dt*(k1x + 2*k2x + 2*k3x + k4x);//Given formula from the website.
			y1 = (0.1666666)*dt*(k1y + 2*k2y + 2*k3y + k4y);//Given formula from the website.
			z1 = (0.1666666)*dt*(k1z + 2*k2z + 2*k3z + k4z);//Given formula from the website.
			
			t_start = t_start + dt; //same as above
			
			x0=x1+x0; //u;dates x0
			y0=y1+y0; //updates y0
			z0=z1+z0; //updates z0
	
		}
		fclose(input); //next lines are the same as euler.
		fclose(output);
		 return 0;
    }
   else
   	return -1;
}
