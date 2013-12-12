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


/*
INTRO: I first made the background, then I added a label, then I created a box, followed by creating
a box that follows the mouse only when you click the mouse, and hold down on the button. Otherwise
the box stays in its original position. When I click my button, I return to the original
screen and when I click start I go to the screen I created. This is all on one window.

*/
#include "WALY/WALY.h"

#include "OneClass.h"
#include "BurstScreen.h"

using namespace WALY;

// static class variables and initialization

OneClass::OneClass
(Frame* parent, void (*switchFunc) (void)) :
Frame (parent), switchAction (switchFunc)
{
	//background info
	Rect r;
	r.x = r.y = 0;
	r.w = 500;
	r.h = 800;
	setScrollRect (r);
	down = false;
	useSolidBackground (0xFF0000); //background is red
	
	//creates a label with green text
	Label* lbl = new Label (this, 250, 200, "A wise saying...", 0x00FF00);
	lbl->setAlign (ALIGN_C); //centers the label
	
	//creates a button
	Button* b = new Button (this, 250, 500, "My Button", 0xFFFFFF, 0x008000);
	b->setAlign(ALIGN_C);
	b->setActionFunc (pressButton);
	
	//sets up a field that can be dragged
	box = new Frame (this, 250, 700);
	box->setAlign (ALIGN_C);
	Rect boxRect;
	boxRect.x = boxRect.y = 0;
	boxRect.w = 80;
	boxRect.h = 50;
	box->setScrollRect (boxRect);
	box->useSolidBackground (0x808080);
	
	//these are the functions pertaining to mouse instructions
	setCallbackFunc (MOUSE_UP, mouseButtonUp);
	setCallbackFunc (MOUSE_DOWN, mouseButtonDown);
	setCallbackFunc (MOUSE_MOTION, mouseMotion);

	deactivate ();
}
void OneClass::activate (void)
{
	setActive (true);
	setVisible (true);
}
void OneClass::deactivate (void)
{
	setVisible (false);
	setActive (false);
}


void OneClass::pressButton (Button* b)
{
	//button returns to the burst screen
	OneClass* wywtcyc =(OneClass*)b->getParent();
	wywtcyc->switchAction();
	
}

void OneClass::mouseMotion (Frame* f, const Event* e)
{
	//if the mouse was clicked, only will the box follow the mouse movement
	
	OneClass* wywtcyc = (OneClass*)f;
    if(wywtcyc->down==true)
    {
		wywtcyc->box->setX (e->motion.x);
		wywtcyc->box->setY (e->motion.y);
    }
    //else nothing happens
	else
		return;
}
void OneClass::mouseButtonDown (Frame* f, const Event* e)
{	
	//when the mouse is pressed down, down is set to true and the box should follow the mouse.
	OneClass* wywtcyc = (OneClass*)f;
	wywtcyc->down = true;
	wywtcyc->box->setX (e->motion.x);
	wywtcyc->box->setY (e->motion.y);

}
void OneClass::mouseButtonUp (Frame* f, const Event* e)
{
	//as long as the mouse button is up, the nothing should be happening
	OneClass* wywtcyc = (OneClass*)f;
	wywtcyc->down = false;
}



