//									tab:8
//
// BurstScreen.h - header file for UIUC ECE198KL Spring 2013 Program 12
//                 burst screen
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
// Author:	    Steve Lumetta
// Version:	    1.01
// Creation Date:   13 April 2013
// Filename:	    BurstScreen.h
// History:
//	SL	1.00	13 April 2013
//		Adapted from Program 11 version.
//	SL	1.01	17 April 2013
//		Added comments for clarity.
//

#if !defined(BURST_SCREEN_H)
#define BURST_SCREEN_H

#include "WALY/WALY.h"

using namespace WALY;

class BurstScreen : public Frame {

    private:
        enum {		// list of images
	    IMG_BURST,
	    NUM_IMGS
	};
        enum {		// list of fonts
	    FNT_LARGE,
	    NUM_FONTS
	};
        enum {		// list of sounds
	    SND_HURRAH,
	    NUM_SOUNDS
	};

	// count of number of instances of this class
        static int32_t numInstances;

	// shared data for the clas
	static Image** image;
	static Font**  font;
	static Sound** sound;

	//
	// Initialize the BurstScreen class (prepare images, sounds, 
	// and fonts--only one shared copy is kept for any number of 
	// class instances).
	//
	static void init (void);

	// Clean up the BurstScreen class: delete images, sounds, and fonts.
	static void cleanUp (void);

	// button used to switch to the student's screen
	Button* startButton;

	//
	// callback provided by prog12main.cpp to switch to the
	// student's screen
	//
	void (*startGameAction) (void);

	// function called when a key is pressed
	static void keystroke (Frame* f, const Event* e);

	// function called when the button on the burst screen is pressed
	static void pressButton (Button* b);

    public:
	// constructor
        BurstScreen (Frame* par, void (*startGameFunc) (void));

	// destructor
	~BurstScreen (void) {
	    if (0 == --numInstances) { cleanUp (); }
	}

	// activate one instance (make visible and handle events)
	void activate (void);

	// deactivate one instance (make invisible and stop handling events)
	void deactivate (void);
};

#endif /* BURST_SCREEN_H */
