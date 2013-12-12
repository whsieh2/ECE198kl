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

#if !defined(ONE_CLASS_H)
#define ONE_CLASS_H

#include "WALY/WALY.h"

using namespace WALY;

class OneClass : public Frame {


	private:
	void (*switchAction) (void);
	static void pressButton (Button* b);
	bool down; //temp variable to see if the mouse clicked down
	Frame *box; // pointer to the box
	static void mouseButtonDown (Frame* f, const Event* e);
	static void mouseButtonUp (Frame* f, const Event* e);
	static void mouseMotion (Frame* f, const Event* e);
	
	public:
	OneClass (Frame* parent, void (*switchFunc) (void));
	void activate(void);
	void deactivate(void);

   
};

#endif /* ONE_CLASS_H */
