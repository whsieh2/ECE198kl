/*									tab:8
 *
 * prog6.c - source file for UIUC ECE198KL Spring 2013 Program 6
 *           student code
 *
 * "Copyright (c) 2013 by Vinay Nagar."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Vinay Nagar
 * Version:	    1.01
 * Creation Date:   25 February 2013
 * Filename:	    prog6.c
 * History:
 *	VN	1.00	25 February 2013
 *		First created.
 *	SL	1.01	25 February 2013
 *		Edited headers.
 */

#include <math.h>


#include "prog7.h"
#define PI 3.14159265359

/*
 * getRadius -- returns the radius based on sigma value 
 *               described in the assignment specification
 * INPUTS: sigma -- sigma in the Gaussian distribution 
 * OUTPUTS: none
 * RETURN VALUE: radius -- radius of the filter 
 * SIDE EFFECTS: none 
 */

int getRadius(double sigma) 
{
	int radius = ceil(3*sigma);
    return radius;
}

/*
 * calculateGFilter -- calculates the Gaussian filter  
 * INPUTS: gFilter -- space for a filter (getRadius x getRadius doubles)
 *         sigma -- sigma of Gaussian function
 * OUTPUTS: gFilter(contents) -- pointer to calculated Gaussian values  
 * RETURN VALUE: none 
 * SIDE EFFECTS: none 
 */

void
calculateGFilter(double *gFilter, double sigma)
{
   double x;
   double y;
   double radius = getRadius(sigma);
   double weight = 0;
   double temp;
   int i=0;
   
   for (x = 0; x< 2*radius+1; x++)
   {
   		for (y = 0; y < 2*radius+1; y++)
   		{
   			gFilter[i] = (1/(sqrt(2*PI*sigma*sigma))) * exp(-((pow(x-radius,2))+(pow(y-radius,2)))/
   			(2*sigma*sigma));
   			weight += gFilter[i];
   			i++;
   		}
   }
   i=0;
   for (x = 0; x< 2*radius+1; x++)
   {
   		for (y = 0; y < 2*radius+1; y++)
   		{
   			temp = gFilter[i];
   			gFilter[i] = temp/weight;
   			i++;
   		}
   }
}

/*
 * blurImage -- blurs the image using image convolution. 
 *              alpha channel is also included in convolution.  
 * INPUTS:  in_red -- pointer to the input red channel
 *          in_green -- pointer to the input green channel
 *          in_blue -- pointer to the input blue channel
 *          in_alpha -- pointer to the input alpha channel
 *          gFilter -- pointer to the Gaussian filter
 *          sigma -- sigma of Gaussian distribution
 *          height -- height of the image
 *          width -- width of the image
 * OUTPUTS: out_red(contents) -- blurred red channel output
 *          out_green(contents) -- blurred green channel output
 *          out_blue(contents) -- blurred blue channel output
 *          out_alpha(contents) -- blurred alpha channel output
 * RETURN VALUE: none 
 * SIDE EFFECTS: none 
 */

void blurImage (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, 
		uint8_t *in_alpha, uint8_t *out_red, uint8_t *out_green, 
		uint8_t *out_blue, uint8_t *out_alpha, double *gFilter, 
		double sigma, int height, int width)
{
	int i,j,k,l, rX, rY;
	double sumRed = 0;
	double sumGreen = 0;
	double sumBlue = 0;
	double sumAlpha = 0;
	int radius = getRadius(sigma);
	if (radius < 1)
		return;
	
	for (i=0; i<height; i++)
	{
		for (j=0; j<width; j++)
		{
			for (k=0; k<(2*radius+1); k++)
			{
	   			for (l=0; l<(2*radius+1); l++)
	   			{
					rX = k - radius;
	   				rY = l - radius;
	   				
	   				if(j + rX < width && i + rY < height && j + rX >= 0 && i + rY >= 0)
	   				{
		   				sumRed = sumRed+((in_red[(i + rY)*width + (j + rX)])*(gFilter[l*(2*radius+1) + k]));  
		   				sumGreen = sumGreen+((in_green[(i + rY)*width + (j + rX)])*(gFilter[l*(2*radius+1) + k]));  
		   				sumBlue = sumBlue+ ((in_blue[(i + rY)*width + (j + rX)])*(gFilter[l*(2*radius+1) + k]));  
		   				sumAlpha = sumAlpha+ ((in_alpha[(i + rY)*width + (j + rX)])*(gFilter[l*(2*radius+1) + k]));
		   				
		   				
		   			}
		   			
		   			
		   		}
		   	}
		   	if (sumRed>255)
						   	sumRed=255;
						if (sumRed<0)
						   	sumRed=0;
			
		
						if (sumGreen>255)
							sumGreen = 255;
						if (sumGreen<0)
							sumGreen = 0;
				
						   				
						   			
						if (sumBlue>255)
							sumBlue=255;
						if (sumBlue<0)
							sumBlue=0;
						  
						   				
						   			
						if (sumAlpha>255)
							sumAlpha=255;
						if (sumAlpha<0)
							sumAlpha=0;
							
		   				out_red[i *width+j] = sumRed;
		   				out_green[i *width+j] = sumGreen;
		   				out_blue[i *width+j] = sumBlue;
		   				out_alpha[i *width+j]= sumAlpha;
		   				sumRed =0;
		   				sumBlue=0;
		   				sumGreen=0;
		   				sumAlpha=0;
		   	
		
		}
	}
}

/*
 * convertToGray -- converts the image to gray scale. Output alpha
 *              channel will be retained from the input channel.  
 * INPUTS:  in_red -- pointer to the input red channel
 *          in_green -- pointer to the input green channel
 *          in_blue -- pointer to the input blue channel
 *          in_alpha -- pointer to the input alpha channel
 *          gMonoMult -- pointer to the array which has the constants
 *                       to be multiplied with the RGB channels. Declared as
 *                       gMonoMult[3]  = {0.299f, 0.587f, 0.114f}; 
 *          height -- height of the image
 *          width -- width of the image
 * OUTPUTS: out_red(contents) -- grayscale red channel output
 *          out_green(contents) -- grayscale green channel output
 *          out_blue(contents) -- grayscale blue channel output
 *          out_alpha(contents) -- grayscale alpha channel output
 * RETURN VALUE: none 
 * SIDE EFFECTS: none 
 */

void convertToGray (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, 
		    uint8_t *in_alpha, uint8_t *out_red, uint8_t *out_green, 
		    uint8_t *out_blue, uint8_t *out_alpha, 
		    const float *gMonoMult, int height, int width)
{
     
}

/*
 * rotate90Clockwise -- rotates the image by 90 degrees clockwise 
 * INPUTS:  in_red -- pointer to the input red channel
 *          in_green -- pointer to the input green channel
 *          in_blue -- pointer to the input blue channel
 *          in_alpha -- pointer to the input alpha channel
 *          height -- height of the image
 *          width -- width of the image
 * OUTPUTS: out_red(contents) -- rotated red channel output
 *          out_green(contents) -- rotated green channel output
 *          out_blue(contents) -- rotated blue channel output
 *          out_alpha(contents) -- rotated alpha channel output
 * RETURN VALUE: none 
 * SIDE EFFECTS: none 
 */

void rotate90Clockwise (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue,
			uint8_t *in_alpha, uint8_t *out_red, 
			uint8_t *out_green, uint8_t *out_blue, 
			uint8_t *out_alpha, int height, int width)
{
  
}

/*
 * invertColors -- inverts the colors of the image. Alpha
 *              channel will be retained from the input channel.  
 * INPUTS:  in_red -- pointer to the input red channel
 *          in_green -- pointer to the input green channel
 *          in_blue -- pointer to the input blue channel
 *          in_alpha -- pointer to the input alpha channel
 *          height -- height of the image
 *          width -- width of the image
 * OUTPUTS: out_red(contents) -- inverted red channel output
 *          out_green(contents) -- inverted green channel output
 *          out_blue(contents) -- inverted blue channel output
 *          out_alpha(contents) -- inverted alpha channel output
 * RETURN VALUE: none 
 * SIDE EFFECTS: none 
 */

void invertColors (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, 
		   uint8_t *in_alpha, uint8_t *out_red, uint8_t *out_green, 
		   uint8_t *out_blue, uint8_t *out_alpha, int height, 
		   int width)
{
   
}

/*
 * linearDodge -- implements the linear dodge effect on two images. 
 *                Alpha channel will be included in the process. 
 * INPUTS:  in_red -- pointer to the input red channel
 *          in_green -- pointer to the input green channel
 *          in_blue -- pointer to the input blue channel
 *          in_alpha -- pointer to the input alpha channel
 *          out_red -- pointer to the second image's red channel
 *          out_green -- pointer to the second image's green channel
 *          out_blue -- pointer to the second image's blue channel
 *          out_alpha -- pointer to the second image's alpha channel
 *          amount -- amount of the dodge (blending)
 *          height -- height of the image
 *          width -- width of the image
 * OUTPUTS: out_red(contents) -- resulting red channel output
 *          out_green(contents) -- resulting green channel output
 *          out_blue(contents) -- resulting blue channel output
 *          out_alpha(contents) -- resulting alpha channel output
 * RETURN VALUE: none 
 * SIDE EFFECTS: none 
 */

void linearDodge (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, 
		  uint8_t *in_alpha, uint8_t *out_red, uint8_t *out_green, 
		  uint8_t *out_blue, uint8_t *out_alpha, double amount, 
		  int height, int width)
{
   
}

/*
 * pixelateImage -- pixelate the image based on the block size 
 * INPUTS:  in_red -- pointer to the input red channel
 *          in_green -- pointer to the input green channel
 *          in_blue -- pointer to the input blue channel
 *          in_alpha -- pointer to the input alpha channel
 *          pixelatex -- width of the block
 *          pixelatey -- height of the block
 *          height -- height of the image
 *          width -- width of the image
 * OUTPUTS: out_red(contents) -- pixelated red channel output
 *          out_green(contents) -- pixelated green channel output
 *          out_blue(contents) -- pixelated blue channel output
 *          out_alpha(contents) -- pixelated alpha channel output
 * RETURN VALUE: none 
 * SIDE EFFECTS: none 
 */

void pixelateImage (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, 
		    uint8_t *in_alpha, uint8_t *out_red, uint8_t *out_green, 
		    uint8_t *out_blue, uint8_t *out_alpha, int pixelatex, 
		    int pixelatey, int height, int width)
{
   
}
