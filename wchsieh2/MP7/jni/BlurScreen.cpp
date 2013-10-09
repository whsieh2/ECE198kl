//									tab:8
//
// BlurScreen.cpp - source file for UIUC ECE198KL Spring 2013 Program 7
//                  image processing program screen
//
// "Copyright (c) 2013 by Steven S. Lumetta."
//
// Permission to use, copy, modify, and distribute this software and its
// documentation for any purpose, without fee, and without written agreement is
// hereby granted, provided that the above copyright notice and the following
// two paragraphs appear in all copies of this software.
// 
// IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO 
// ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL 
// DAMAGES ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, 
// EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED 
// OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE 
// PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
// THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE, 
// SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
//
// Author:	    Steve Lumetta, Vinay Nagar
// Version:	    1.00
// Creation Date:   25 February 2013
// Filename:	    BlurScreen.cpp
// History:
//	VN	1.00	25 February 2013
//		First written.
//

#include "WALY/WALY.h"

#include <math.h>

#include "BlurScreen.h"
#include "prog7.h"

using namespace WALY;

int32_t BlurScreen::numInstances = 0;
float BlurScreen::sigma          = 0;
float BlurScreen::radius         = 0;
Font*   BlurScreen::font         = NULL;
Sound*  BlurScreen::sound        = NULL;
Image** BlurScreen::image        = NULL;
Frame *imgFrame                  = NULL;
uint8_t** BlurScreen::channels   = NULL;
uint8_t** BlurScreen::aux        = NULL;
double* BlurScreen::gFilter      = NULL;

static int height                = 0;
static int width                 = 0;

static uint8_t* comb             = NULL;

const static float gMonoMult[3]  = {0.299f, 0.587f, 0.114f};

void
BlurScreen::init ()
{
    font = new Font (WALY_FONT_SANS_REGULAR, 30);

    sound = new Sound ("buttonPress.wav");

    static const char* const names[NUM_IMAGES] = {
    		"smiley.png",
    		"smiley.png",
                "black.png"
    };

    image = new Image*[NUM_IMAGES];
    for (int32_t i = 0; NUM_IMAGES > i; i++) {
    	image[i] = new Image (names[i]);
    }

    channels = new uint8_t*[NUM_CHANNELS*2];
    aux = new uint8_t*[NUM_CHANNELS];
   
    /* initialize input pointers to image */
    Surface* inputImageData = image[INPUT]->getImageData();

    /* first four channels are for input */
    channels[0] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    channels[1] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    channels[2] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    channels[3] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);

    /* below four channels are for output */
    channels[4] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    channels[5] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    channels[6] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    channels[7] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);

    /* below four channels are for output */
    aux[0] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    aux[1] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    aux[2] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);
    aux[3] = (uint8_t*)malloc(IMAGE_WIDTH*IMAGE_WIDTH);

    uint8_t *temp = (uint8_t*)image[INPUT]->getImageData()->pixels;
    long index = 0;

    /* initialize each channel array */
    for (int i = 0; i < IMAGE_WIDTH*IMAGE_WIDTH*4; i = i+4) {
	channels[0][index] = temp[i];
	channels[1][index] = temp[i+1];
        channels[2][index] = temp[i+2];
        channels[3][index] = temp[i+3];
        index++;
    }

    /* Initialize height and width */
    height = inputImageData->h;
    width  = inputImageData->w;

    comb = (uint8_t*)malloc(IMAGE_WIDTH * IMAGE_WIDTH * NUM_CHANNELS);
}

void
BlurScreen::cleanUp ()
{
    delete font;
    font = NULL;
    delete sound;
    sound = NULL;

    int i = 0;
    for (i = 0; i < NUM_CHANNELS*2; i++) {
        free(channels[i]);
    }

    for (i = 0; i < NUM_CHANNELS; i++) {
        free(aux[i]);
    }

    free(comb);

    delete channels;
}

void
BlurScreen::pushButton (Button* b)
{ 
    char buf[1024]; /* doing it everytime the button is pressed*/
    BlurScreen* bs = (BlurScreen*)b->getParent ();
   
    bool image_button = false;

    if (bs->incButton == b) {
        sigma = sigma + 0.5;
	sprintf (buf, "%0.2f", sigma);
	bs->display->setText (buf);
    } else if (bs->decButton == b) {
        if (sigma > 0) {
            sigma = sigma - 0.5;
            sprintf (buf, "%0.2f", sigma);
	    bs->display->setText (buf);
        }
    } else if (bs->blurButton == b) {
         image_button = true;
         radius = ceil(3 * sigma);
         int gLength =  2 * radius + 1; 
         gFilter = (double *)malloc(gLength * gLength * sizeof(double));
         calculateGFilter(gFilter, sigma);
         blurImage(channels[0], channels[1], channels[2], channels[3], 
                   channels[4], channels[5], channels[6], channels[7], 
                   gFilter, sigma, height, width);
    } else if (bs->pixButton == b) {
         image_button = true;
         pixelateImage(channels[0], channels[1], channels[2], channels[3],
                   channels[4], channels[5], channels[6], channels[7],
                   12, 12, height, width);
    } else if (bs->pencilButton == b) {
         image_button = true;
         invertColors(channels[0], channels[1], channels[2], channels[3],
                      aux[0], aux[1], aux[2], aux[3],
                      height, width);
         radius = ceil(3 * 1.5);
         int gLength =  2 * radius + 1; 
         gFilter = (double *)malloc(gLength * gLength * sizeof(double));
         calculateGFilter(gFilter, 1.5);
         blurImage(aux[0], aux[1], aux[2], aux[3],
                   channels[4], channels[5], channels[6], channels[7],
                   gFilter, 1.5, height, width);
         linearDodge(channels[0], channels[1], channels[2], channels[3],
                      channels[4], channels[5], channels[6], channels[7],
                      0.98, height, width);
         convertToGray(channels[4], channels[5], channels[6], channels[7],
                   channels[4], channels[5], channels[6], channels[7],
                   gMonoMult, height, width);
    } else {
         image_button = true;
         rotate90Clockwise(channels[0], channels[1], channels[2], channels[3], 
                   channels[4], channels[5], channels[6], channels[7], 
                   height, width);
    } 
    if (image_button) {      
        long index = 0;
        for (int i = 0; i < IMAGE_WIDTH*IMAGE_WIDTH; i++) {
            comb[index++] = channels[4][i];
            comb[index++] = channels[5][i];
            comb[index++] = channels[6][i];
            comb[index++] = channels[7][i];
        }
        image[OUTPUT]->getImageData()->pixels = comb;
        imgFrame->attachImage (image[OUTPUT]);
    }
}

BlurScreen::BlurScreen (Frame* par) : Frame (par)
{
    Rect r;

    if (0 == numInstances++) { init (); }

    useSolidBackground (0x383838);
    r.x = r.y = 0;
    r.w = 500;
    r.h = 800;
    setScrollRect (r);

    imgFrame = new Frame (this, 240, 320);
    imgFrame->attachImage (image[INPUT]);
    imgFrame->setAlign (ALIGN_C);

    blurButton = new Button
               (this, 220, 720, "Blur", 0x000000, 0x009000, font);
    blurButton->setAlign (ALIGN_N);
    blurButton->setActionFunc (pushButton);

    pixButton = new Button
               (this, 350, 720, "Pixelate", 0x000000, 0x009000, font);
    pixButton->setAlign (ALIGN_N);
    pixButton->setActionFunc (pushButton);

    rotateButton = new Button
               (this, 220, 660, "Rotate", 0x000000, 0x009000, font);
    rotateButton->setAlign (ALIGN_N);
    rotateButton->setActionFunc (pushButton);

    pencilButton = new Button
               (this, 350, 660, " Pencil ", 0x000000, 0x009000, font);
    pencilButton->setAlign (ALIGN_N);
    pencilButton->setActionFunc (pushButton);

    incButton = new Button
               (this, 50, 720, " + ", 0x000000, 0x009000, font);
    incButton->setAlign (ALIGN_N);
    incButton->setActionFunc (pushButton);

    decButton = new Button
               (this, 120, 720, " -  ", 0x000000, 0x009000, font);
    decButton->setAlign (ALIGN_N);
    decButton->setActionFunc (pushButton);

    display = new EntryBox (this, 25, 660, 100, "0", 0x00FF00, 
    			    0x000000, font);
    display->setEnabled (false);
    display->setTextAlign (Widget::TEXT_RIGHT);

    setCallbackFunc (KEY_DOWN, keystroke);

    setVisible (false);
    setActive (false);
}

void
BlurScreen::keystroke (Frame* f, const Event* e)
{
    BlurScreen* bs = (BlurScreen*)f;
    int32_t key = e->key.keysym.sym;
    int32_t shifted = (e->key.keysym.mod & KMOD_SHIFT);
}

void
BlurScreen::activate ()
{
    setActive (true);
    setVisible (true);
}

void
BlurScreen::deactivate ()
{
    setVisible (false);
    setActive (false);
}

