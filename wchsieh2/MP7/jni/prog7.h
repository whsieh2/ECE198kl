/*									tab:8
 *
 * prog6.h - header file for UIUC ECE198KL Spring 2013 Program 6
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
 * Version:	    1.00
 * Creation Date:   25 February 2013
 * Filename:	    prog4.h
 * History:
 *	VN	1.00	25 February 2013
 *		First created.
 */

#if !defined(PROG6_)
#define PROG6_

#include <stdint.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)

#define IMAGE_WIDTH 512 /* we will stick to 512 X 512 images */
#define IMAGE_HEIGHT 512 /* we will stick to 512 X 512 images */
#define NUM_CHANNELS 4 /* four channels including alpha */
#define NUM_IMAGES 3 /* number of images including input and output */

enum {
    INPUT   = 0,
    OUTPUT  = 1,
};

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                   PROGRAM 6 EXTERNALLY VISIBLE FUNCTIONS                 */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* 
 * Called each time the "Blur" button is pressed. It creates a Gaussian kernel 
 * populating the values in memory pointed to by gKernel based on the sigma value. 
 */
void calculateGFilter (double *gKernel, double sigma);

/* 
 * Called each time the "Blur" button is pressed. It blurs the image using image
 * convolution. It takes as input, four arrays representing the four channels,
 * red, green, blue and alpha. It also takes the Gaussian filter, sigma, image's height,
 * width and returns the blurred image.
 */

void blurImage (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                double *gFilter, double sigma, int height, int width);

/* 
 * Converts the image to gray scale. This function is important in the pencil sketch effect
 * process. It takes as input, four arrays representing the four channels,
 * red, green, blue and alpha. It also takes a pointer gMonoMult which points to the array
 * used to multiply with the RGB values to get the gray scale.
 */
void convertToGray (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                const float *gMonoMult, int height, int width);

/*
 * Rotates the image 90 degrees clockwise one time. Simultaneous "Rotate" button presses
 * will not rotate the image again.
 */ 

void rotate90Clockwise (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                int height, int width);

/* 
 * Inverts the colors of the image. This function is part of pencil sketch effect. Each pixel
 * is set to color equal to '255 - c' where 'c' is the color of the pixel in each channel.
 */
  
void invertColors (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                int height, int width);

/* 
 * A linear blending mode of two images. This function is also part of pencil sketch effect. 
 * The amount parameter determines the amount of blend between the two images. In pencil sketch
 * effect, first image is the unaltered source image and the second image is the blurred source image 
 */
void linearDodge (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                double amount, int height, int width);
/*
 * Pixelates the image based on the block size. pixelatex and pixelatey represent the block size
 * in horizontal and vertical dimensions respectively. Each pixel in the block is set to the average
 * of all the pixel values in that block.
 */
void pixelateImage (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                int pixelatex, int pixelatey, int height, int width);

#if defined(__cplusplus)
}
#endif //defined(__cplusplus)

#endif /* PROG6_ */
