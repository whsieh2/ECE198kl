//									tab:8
//
// BlurScreen.h - header file for UIUC ECE198KL Spring 2013 Program 7
//                image processing program screen
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
// Filename:	    BlurScreen.h
// History:
//	VN	1.00	25 February 2013
//		First written.
//

#if !defined(BLUR_SCREEN_H)
#define BLUR_SCREEN_H

#include "WALY/WALY.h"

using namespace WALY;

class BlurScreen : public Frame {

    private:
        static int32_t numInstances;
        static float sigma;
        static float radius;
        static Font* font;
	static Sound* sound;
	static Image** image;
        static uint8_t **channels;
        static uint8_t **aux;

        static double *gFilter;
        
	Button* blurButton;
	Button* pixButton;
	Button* rotateButton;
	Button* pencilButton;
        Button* incButton;
        Button* decButton;

	static void init ();
	static void cleanUp ();

	EntryBox* display;

	static void applyAction (EntryBox* display, int32_t action);

	static void pushButton (Button* b);
	static void keystroke (Frame* f, const Event* e);


    public:
        BlurScreen (Frame* par);
	~BlurScreen () {
	    if (0 == --numInstances) { cleanUp (); }
	}

	void activate ();
	void deactivate ();
};

#endif /* BLUR_SCREEN_H */
