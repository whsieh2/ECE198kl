//									tab:8
//
// prog4main.cpp - source file for UIUC ECE198KL Spring 2013 Program 4
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
// Creation Date:   2 February 2013
// Filename:	    prog4main.cpp
// History:
//	SL	1.00	2 February 2013
//		First written.
//

#include <iostream>

#include "WALY.h"

#include "WALYmain.h"
#include "BlurScreen.h"

using namespace std;
using namespace WALY;

static DebugFile*       dbg             = NULL;
static Frame*           rootFrame       = NULL;
static BlurScreen*      blurScreen      = NULL;

int 
WALY_main ()
{
    rootFrame = Screen::createRootFrame (500, 800);

    // create the output file for debugging...
    dbg = DebugFile::createDebugFile ();
    dbg->getStream () << "----- START OF DEBUG OUTPUT -----" << endl;
    Screen::setDebugOutput (&dbg->getStream ());
 
    blurScreen = new BlurScreen (rootFrame);

    blurScreen->activate ();

    Screen::run ();

    delete blurScreen;

    dbg->getStream () << "----- END OF DEBUG OUTPUT -----" << endl;
    delete dbg;

    delete rootFrame;

    return 0;
}

