//									tab:8
//
// prog12main.cpp - source file for UIUC ECE198KL Spring 2013 Program 12
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
// Version:	    1.00
// Creation Date:   13 April 2013
// Filename:	    prog12main.cpp
// History:
//	SL	1.00	13 April 2013
//		Adapted from previous program version.
//

#include <stdarg.h>

#include <iostream>

#include "WALY.h"

#include "WALYmain.h"
#include "BurstScreen.h"

using namespace std;
using namespace WALY;

static DebugFile*   dbg         = NULL;
static Frame*       rootFrame   = NULL;
static BurstScreen* burstScreen = NULL;

static void 
startGame (void)
{
    burstScreen->deactivate ();
    // You need to activate your class instance here (and remove
    // the activation of the burst screen below).

    //
    // If we leave nothing active, nothing is drawn to the screen
    // (but whatever was on the screen last remains there, so the
    // program appears to be frozen/hung).
    //
    burstScreen->activate ();
}

static void
returnToBurst (void)
{
    // Pass this function to your class' constructor, then
    // call it in response to a button press to switch back to
    // the burst screen view.

    // You need to deactivate your class instance here.


    // Then we activate the burst screen.
    burstScreen->activate ();
}

int 
WALY_main (void)
{
    rootFrame = Screen::createRootFrame (500, 800);

    // create the output file for debugging...
    dbg = DebugFile::createDebugFile ();
    dbg->getStream () << "----- START OF DEBUG OUTPUT -----" << endl;
    Screen::setDebugOutput (&dbg->getStream ());
 
    burstScreen = new BurstScreen (rootFrame, startGame);

    burstScreen->activate ();

    Screen::run ();

    delete burstScreen;

    dbg->getStream () << "----- END OF DEBUG OUTPUT -----" << endl;
    delete dbg;

    delete rootFrame;

    return 0;
}

