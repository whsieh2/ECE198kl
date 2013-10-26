#include "jni/prog7.h"
#include "jni/prog7.c"

#include "solution.h"

const static float gMonoMult[3]  = {0.299f, 0.587f, 0.114f};

int main() 
{
    int ret = 0, i = 0;
    uint8_t **testinput = new uint8_t*[NUM_CHANNELS*2];
    uint8_t **soloutput = new uint8_t*[NUM_CHANNELS*2];
    uint8_t **myoutput = new uint8_t*[NUM_CHANNELS*2];

    testinput[0] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    testinput[1] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    testinput[2] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    testinput[3] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);

    soloutput[0] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    soloutput[1] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    soloutput[2] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    soloutput[3] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);

    myoutput[0] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    myoutput[1] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    myoutput[2] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    myoutput[3] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);

    /* initialize random values to input array */
    initialize_input(testinput[0], testinput[1], testinput[2], testinput[3]);

    for (i = 0; i < NUM_CHANNELS; ++i) {
        memset(soloutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH); 
        memset(myoutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH); 
    }

    /* check calculateGFilter */
    double sigma = 2.0;
    int radius = 6;
    double *gFilter_sol = (double *)malloc(13 * 13 * sizeof(double)); 
    double *gFilter_out = (double *)malloc(13 * 13 * sizeof(double)); 

    calculateGFilter_solution(gFilter_sol, sigma);
    calculateGFilter(gFilter_out, sigma);

    ret = checkFilterOutputs(gFilter_sol, gFilter_out);
    if (ret) {
        printf("calculateGKernel() failed\n");
    } else {
        printf("calculateGKernel() passed\n");
    }

    /* check blurImage. Use data from the previous function */
    blurImage_solution (testinput[0], testinput[1], testinput[2], testinput[3],
                soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                gFilter_sol, sigma, IMAGE_HEIGHT, IMAGE_WIDTH);

    blurImage (testinput[0], testinput[1], testinput[2], testinput[3],
                myoutput[0], myoutput[1], myoutput[2], myoutput[3],
                gFilter_sol, sigma, IMAGE_HEIGHT, IMAGE_WIDTH);

    /* now test the outputs */
    ret = checkOutputs(soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                 myoutput[0], myoutput[1], myoutput[2], myoutput[3]);

    if (ret) {
        printf("blurImage() failed\n");
    } else {
        printf("blurImage() passed\n");
    }


    /* initialize random values to input array */
    initialize_input(testinput[0], testinput[1], testinput[2], testinput[3]);

    for (i = 0; i < NUM_CHANNELS; ++i) {
        memset(soloutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH);
        memset(myoutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH);
    }

    /* check for invertColors */
    invertColors_solution (testinput[0], testinput[1], testinput[2], testinput[3],
                soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                IMAGE_HEIGHT, IMAGE_WIDTH);

    invertColors (testinput[0], testinput[1], testinput[2], testinput[3],
                myoutput[0], myoutput[1], myoutput[2], myoutput[3],
                IMAGE_HEIGHT, IMAGE_WIDTH);

    /* now test the outputs */
    ret = checkOutputs(soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                 myoutput[0], myoutput[1], myoutput[2], myoutput[3]);

    if (ret) {
        printf("invertColors() failed\n");
    } else {
        printf("invertColors() passed\n");
    }


    /* initialize random values to input array */
    initialize_input(testinput[0], testinput[1], testinput[2], testinput[3]);

    for (i = 0; i < NUM_CHANNELS; ++i) {
        memset(soloutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH);
        memset(myoutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH);
    }

    /* check for linearDodge */
    linearDodge_solution (testinput[0], testinput[1], testinput[2], testinput[3],
                soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                0.98, IMAGE_HEIGHT, IMAGE_WIDTH);
    
    linearDodge (testinput[0], testinput[1], testinput[2], testinput[3],
                myoutput[0], myoutput[1], myoutput[2], myoutput[3],
                0.98, IMAGE_HEIGHT, IMAGE_WIDTH);

    /* now test the outputs */
    ret = checkOutputs(soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                 myoutput[0], myoutput[1], myoutput[2], myoutput[3]);

    if (ret) {
        printf("linearDodge() failed\n");
    } else {
        printf("linearDodge() passed\n");
    }


    /* initialize random values to input array */
    initialize_input(testinput[0], testinput[1], testinput[2], testinput[3]);

    for (i = 0; i < NUM_CHANNELS; ++i) {
        memset(soloutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH);
        memset(myoutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH);
    }
 

    /* check for convertGrayScale */
    convertToGray_solution (testinput[0], testinput[1], testinput[2], testinput[3],
                soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                gMonoMult, IMAGE_HEIGHT, IMAGE_WIDTH);

    convertToGray (testinput[0], testinput[1], testinput[2], testinput[3],
                myoutput[0], myoutput[1], myoutput[2], myoutput[3],
                gMonoMult, IMAGE_HEIGHT, IMAGE_WIDTH);

    for (i = 0; i < NUM_CHANNELS; ++i) {
        memset(soloutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH); 
        memset(myoutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH); 
    }

    /* now test the outputs */
    ret = checkOutputs(soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                 myoutput[0], myoutput[1], myoutput[2], myoutput[3]);

    if (ret) {
        printf("convertToGray() failed\n");
    } else {
        printf("convertToGray() passed\n");
    }

    /* initialize input */
    initialize_input(testinput[0], testinput[1], testinput[2], testinput[3]);
    
    for (i = 0; i < NUM_CHANNELS; ++i) {
        memset(soloutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH);
        memset(myoutput[i], -1, IMAGE_WIDTH*IMAGE_WIDTH);
    }

    /*check for convertGrayScale */ 
    pixelateImage_solution (testinput[0], testinput[1], testinput[2], testinput[3],
                soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                12, 12, IMAGE_HEIGHT, IMAGE_WIDTH);

    pixelateImage (testinput[0], testinput[1], testinput[2], testinput[3],
                myoutput[0], myoutput[1], myoutput[2], myoutput[3],
                12, 12, IMAGE_HEIGHT, IMAGE_WIDTH);


    /* now test the outputs */
    ret = checkOutputs(soloutput[0], soloutput[1], soloutput[2], soloutput[3],
                 myoutput[0], myoutput[1], myoutput[2], myoutput[3]);

    if (ret) {
        printf("pixelateImage() failed\n");
    } else {
        printf("pixelateImage() passed\n");
    }


    for (i = 0; i < NUM_CHANNELS/2; ++i) {
        free(soloutput[i]);
        free(myoutput[i]);
        free(testinput[i]);
    } 

    free(gFilter_sol);
    free(gFilter_out);
    delete soloutput;
    delete myoutput;
    delete testinput;

    return 0;
}
