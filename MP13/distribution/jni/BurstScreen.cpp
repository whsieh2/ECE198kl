//									tab:8
//
// BurstScreen.cpp - source file for UIUC ECE198KL Spring 2013 Program 12
//                   burst screen
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
// Filename:	    BurstScreen.cpp
// History:
//	SL	1.00	13 April 2013
//		Adapted from Program 11 version.
//	SL	1.01	17 April 2013
//		Added comments for clarity.
//

#include "WALY/WALY.h"

#include "BurstScreen.h"

using namespace WALY;

// static class variables and initialization
int32_t BurstScreen::numInstances = 0;
Image** BurstScreen::image        = NULL;
Font**  BurstScreen::font         = NULL;
Sound** BurstScreen::sound        = NULL;


//
// This function is called when the first instance is created (any
// time there are no other instances in existence).  It loads images
// and sounds from disk and prepares fonts.  Images, sounds, and fonts
// are shared among all instances (no need to have lots of copies).
//
void
BurstScreen::init ()
{ 
    static const char* const names[NUM_IMGS] = {
        "burstImage.png",
    };
    image = new Image*[NUM_IMGS];
    for (int32_t i = 0; NUM_IMGS > i; i++) {
        image[i] = new Image (names[i]);
    }

    static const char* const fontNames[NUM_FONTS] = {
        WALY_FONT_SANS_REGULAR
    };
    static const int32_t fontSizes[NUM_FONTS] = {
        40
    };
    font = new Font*[NUM_FONTS];
    for (int32_t i = 0; NUM_FONTS > i; i++) {
        font[i] = new Font (fontNames[i], fontSizes[i]);
    }

    static const char* const soundNames[NUM_SOUNDS] = {
        "hurrah.wav",
    };
    sound = new Sound*[NUM_SOUNDS];
    for (int32_t i = 0; NUM_SOUNDS > i; i++) {
        sound[i] = new Sound (soundNames[i]);
    }
}

//
// This function is called when the last instance of the class is 
// destroyed.  Image, sound, and font data are deleted.
//
void
BurstScreen::cleanUp ()
{
    for (int32_t i = 0; NUM_IMGS > i; i++) {
	delete image[i];
    }
    delete[] image;
    image = NULL;

    for (int32_t i = 0; NUM_FONTS > i; i++) {
	delete font[i];
    }
    delete[] font;
    font = NULL;

    for (int32_t i = 0; NUM_SOUNDS > i; i++) {
	delete sound[i];
    }
    delete[] sound;
    sound = NULL;
}

//
// This functio is called when the button in the burst screen is pressed.
// It executes the callback provided by prog12main.cpp.
//
void 
BurstScreen::pressButton (Button* b)
{
    BurstScreen* bs = (BurstScreen*)b->getParent ();

    bs->startGameAction ();
}

// constructor
BurstScreen::BurstScreen (Frame* par, void (*startGameFunc) ()) : 
	Frame (par), startGameAction (startGameFunc)
{
    Rect r;

    // Initialize the class, if necessary.  Count this instance.
    if (0 == numInstances++) { init (); }

    // Set up opaque background.
    useSolidBackground (0x101060);
    r.x = r.y = 0;
    r.w = 500;
    r.h = 800;
    setScrollRect (r);

    // Draw the burst image.
    Frame* f = new Frame (this, 250, 200);
    f->setAlign (ALIGN_C);
    f->attachImage (image[IMG_BURST]);

    // Create the button used to switch to the student's class' screen.
    startButton = new Button (this, 250, 400, "Start",
			      0xFFFFFF, 0x004000, font[FNT_LARGE]);
    startButton->setAlign (ALIGN_C);
    startButton->setActionFunc (pressButton);

    // Register for keystrokes.
    setCallbackFunc (KEY_DOWN, keystroke);

    // Start deactivated.
    deactivate ();
}
	
// 
// This function is called when a key is pressed.  The Nexus' back button
// and the Escape key cause minimization of the program.  Other keys are
// ignored.
//
void 
BurstScreen::keystroke (Frame* f, const Event* e)
{
    if (PDLK_GESTURE_BACK == (int32_t)e->key.keysym.sym) {
        Platform::minimize ();
    }
}

//
// Make the burst screen visible, handle events (keystrokes), and play
// a sound.
//
void
BurstScreen::activate (void)
{
    sound[SND_HURRAH]->play ();
    setActive (true);
    setVisible (true);
}

//
// Make the burst screen invisible and stop handling events (keystrokes).
//
void
BurstScreen::deactivate (void)
{
    setVisible (false);
    setActive (false);
}

