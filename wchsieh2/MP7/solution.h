#if !defined(SOL6_)
#define SOL6_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "jni/prog7.h"

#define IMAGE_HEIGHT 512
#define IMAGE_WIDTH 512

int checkOutputs (uint8_t *exp_red, uint8_t *exp_green, uint8_t *exp_blue, uint8_t *exp_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha);

void initialize_input (uint8_t *red, uint8_t *green, uint8_t *blue, uint8_t *alpha);

void convertToGray_solution (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                const float *gMonoMult, int height, int width);

void calculateGFilter_solution (double *gKernel, double sigma);

void blurImage_solution (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha, 
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                double *gKernel, double sigma, int height, int width);

void rotate90Clockwise_solution (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                int height, int width);

void invertColors_solution (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                int height, int width);

void linearDodge_solution (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                double amount, int height, int width);

void pixelateImage_solution (uint8_t *in_red, uint8_t *in_green, uint8_t *in_blue, uint8_t *in_alpha,
                uint8_t *out_red, uint8_t *out_green, uint8_t *out_blue, uint8_t *out_alpha,
                int pixelatex, int pixelatey, int height, int width);

int checkFilterOutputs (double *sol, double *out);

#endif
