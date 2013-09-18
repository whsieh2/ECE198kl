//									tab:8
//
// CalcScreen.cpp - source file for UIUC ECE198KL Spring 2013 Program 4
//                  calculator screen
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
// Filename:	    CalcScreen.cpp
// History:
//	SL	1.00	2 February 2013
//		First written.
//

#include "WALY/WALY.h"

#include <math.h>

#include "CalcScreen.h"
#include "prog4.h"

using namespace WALY;

int32_t CalcScreen::numInstances = 0;
Font**  CalcScreen::font         = NULL;
Sound*  CalcScreen::sound        = NULL;

void
CalcScreen::init ()
{
    font = new Font*[3];
    font[0] = new Font (WALY_FONT_MONO_BOLD, 50);
    font[1] = new Font (WALY_FONT_SANS_REGULAR, 60);
    font[2] = new Font (WALY_FONT_SANS_REGULAR, 40);

    sound = new Sound ("buttonPress.wav");
}

void
CalcScreen::cleanUp ()
{
    for (int32_t i = 0; 3 > i; i++) {
	delete font[i];
    }
    delete[] font;
    font = NULL;
    delete sound;
    sound = NULL;
}

void
CalcScreen::applyAction (EntryBox* display, int32_t action)
{
    sound->play ();

    char buf[1024]; /* should be big enough--will overflow double... */
    const char* text = display->getText ();
    char* after;
    double value = strtod (text, &after);

    if (text == after) {
	/* Conversion error--pass an error. */
        value = BAD_OPERATION;
    }
    int32_t response = handle_key (action, &value);
    if (RESPONSE_IGNORE == response) {
        // Do nothing.
	return;
    }

    switch (response) {
	case RESPONSE_ECHO_KEY: {
	    char append;

	    if (BUTTON_9 >= action) {
		append = '0' + action - BUTTON_0;
	    } else switch (action) {
		case BUTTON_DEC_PT: append = '.'; break;
		case BUTTON_MINUS:  append = '-'; break;
		case BUTTON_NEGATE: append = '-'; break;
		case BUTTON_EXP:    append = 'e'; break;
		default:
		    Screen::debug () << "echo key returned for action "
				     << action << std::endl;
		    append = '?'; 
		    break;
	    }
	    sprintf (buf, "%.1022s%c", text, append);
	    display->setText (buf);
	    value = strtod (buf, &after);
	    if (buf == after) {
		response = RESPONSE_ERROR;
	    }
	    break;
	}
        case RESPONSE_REPLACE:
	    sprintf (buf, "%.9g", value);
	    display->setText (buf);
	    break;
        case RESPONSE_ERROR:
	    break;
	default:
	    Screen::debug () << "ILLEGAL RESPONSE " << response 
			     << " FROM handle_key" << std::endl;
	    response = RESPONSE_ERROR;
	    break;
    }
    if (RESPONSE_ERROR != response &&
        (INFINITY == value || -INFINITY == value || value != value)) {
	response = RESPONSE_ERROR;
    }
    if (RESPONSE_ERROR == response) {
	display->setText ("Error.");
    }
}

void
CalcScreen::pushButton (Button* b)
{
    CalcScreen* cs = (CalcScreen*)b->getParent ();

    static const int32_t meaning[7][5] = {
        {BUTTON_SIN, BUTTON_COS, BUTTON_TAN, BUTTON_LN, BUTTON_E_TO_X},
        {BUTTON_SQUARE, BUTTON_X_TO_Y, BUTTON_FACT, BUTTON_CBRT, BUTTON_SQRT},
        {BUTTON_MEM_ADD, BUTTON_MEM_SUB, BUTTON_MEM_RECALL, BUTTON_MEM_CLEAR,
	 BUTTON_EXP},
        {BUTTON_INVERT, BUTTON_7, BUTTON_8, BUTTON_9, BUTTON_DIVIDE},
        {BUTTON_NEGATE, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_TIMES},
        {BUTTON_CLEAR_ENTRY, BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_MINUS},
        {BUTTON_ALL_CLEAR, BUTTON_0, BUTTON_DEC_PT, BUTTON_EQUALS, BUTTON_PLUS}
    };

    for (int32_t y = 0; 7 > y; y++) {
	for (int32_t x = 0; 5 > x; x++) {
	    if (cs->button[y][x] == b) {
	    	applyAction (cs->display, meaning[y][x]);
	    }
	}
    }
}

CalcScreen::CalcScreen (Frame* par) : Frame (par)
{
    Rect r;

    if (0 == numInstances++) { init (); }

    useSolidBackground (0x383838);
    r.x = r.y = 0;
    r.w = 500;
    r.h = 800;
    setScrollRect (r);

    display = new EntryBox (this, 10, 35, 470, "0", 0x00FF00, 
    			    0x000000, font[0]);
    display->setEnabled (false);
    display->setTextAlign (Widget::TEXT_RIGHT);

    static const int32_t rowPos[7] = {
        160, 245, 330, 425, 530, 635, 740
    };
    static const int32_t bgColor[7][5] = {
        {0x000080, 0x000080, 0x000080, 0x000080, 0x000080}, 
        {0x000080, 0x000080, 0x000080, 0x000080, 0x000080}, 
        {0x004000, 0x004000, 0x004000, 0x004000, 0x000080}, 
        {0x000080, 0x0000FF, 0x0000FF, 0x0000FF, 0x000080}, 
        {0x000080, 0x0000FF, 0x0000FF, 0x0000FF, 0x000080}, 
        {0xFF4040, 0x0000FF, 0x0000FF, 0x0000FF, 0x000080}, 
        {0xFF4040, 0x0000FF, 0x0000FF, 0x000080, 0x000080}
    };
    static const char* const bLabel[7][5] = {
        {"sin", "cos", "tan", "ln", "e^x"},
        {"x^2", "x^y", "n!", "crt", "sqt"},
        {"M+", "M-", "MR", "MC", "E"},
        {"1/x", "7", "8", "9", "/"},
        {"+/-", "4", "5", "6", "*"},
        {"CE", "1", "2", "3", "-"},
        {"AC", "0", ".", "=", "+"}
    };
    static const int32_t fontIdx[7][5] = {
        {2,2,2,2,2},
        {2,2,2,2,2},
        {2,2,2,2,2},
        {2,1,1,1,2},
        {2,1,1,1,2},
        {2,1,1,1,2},
        {2,1,1,2,2}
    };

    for (int32_t y = 0; 7 > y; y++) {
	for (int32_t x = 0; 5 > x; x++) {
	    button[y][x] = new Button (this, 50 + x * 100, rowPos[y],
	    			       bLabel[y][x], 0xFFFFFF, bgColor[y][x],
				       font[fontIdx[y][x]]);
	    button[y][x]->setWidth (60);
	    button[y][x]->setAlign (ALIGN_C);
	    button[y][x]->setActionFunc (pushButton);
	}
    }

    setCallbackFunc (KEY_DOWN, keystroke);

    setVisible (false);
    setActive (false);
}

void
CalcScreen::keystroke (Frame* f, const Event* e)
{
    CalcScreen* cs = (CalcScreen*)f;
    int32_t key = e->key.keysym.sym;
    int32_t shifted = (e->key.keysym.mod & KMOD_SHIFT);

    if ('0' <= key && '9' >= key && !shifted) {
        applyAction (cs->display, BUTTON_0 + key - '0');
    } else if (SDLK_KP0 <= key && SDLK_KP9 >= key) {
        applyAction (cs->display, BUTTON_0 + key - SDLK_KP0);
    } else {
	switch (key) {
	    case SDLK_KP_PERIOD:
	    case '.':
	        applyAction (cs->display, BUTTON_DEC_PT);
		break;
	    case '=':
		if (shifted) {
		    applyAction (cs->display, BUTTON_PLUS);
		    break;
		}
		/* fall through to EQUALS case... */
	    case SDLK_KP_ENTER:
	    case SDLK_KP_EQUALS:
	    case '\n':
	    case '\r':
	        applyAction (cs->display, BUTTON_EQUALS);
		break;
	    case SDLK_KP_PLUS:
	    case '+':
	        applyAction (cs->display, BUTTON_PLUS);
		break;
	    case SDLK_KP_MINUS:
	    case '-':
	        applyAction (cs->display, BUTTON_MINUS);
		break;
	    case SDLK_KP_MULTIPLY:
	    case '8': /* shifted */
	    case '*':
	        applyAction (cs->display, BUTTON_TIMES);
		break;
	    case SDLK_KP_DIVIDE:
	    case '/':
	        applyAction (cs->display, BUTTON_DIVIDE);
		break;
	    case 'e':
	        applyAction (cs->display, BUTTON_EXP);
		break;
	    case ((int32_t)PDLK_GESTURE_BACK):
		Platform::minimize ();
		break;
	    default:
		break;
	}
    }
}

void
CalcScreen::activate ()
{
    setActive (true);
    setVisible (true);
}

void
CalcScreen::deactivate ()
{
    setVisible (false);
    setActive (false);
}

