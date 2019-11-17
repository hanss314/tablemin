#include <cstdio>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <ctype.h>

#include "input.h"


void InputState::kbDaemon() {
    Display* d = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(d);
    Window curFocus;
    int revert;

    XGetInputFocus (d, &curFocus, &revert);
    XSelectInput(d, curFocus, KeyPressMask|KeyReleaseMask|FocusChangeMask);
    while (running){
        XEvent ev;
        XNextEvent(d, &ev);
        switch (ev.type){
            case FocusOut:
            if (curFocus != root) XSelectInput(d, curFocus, 0);
            XGetInputFocus (d, &curFocus, &revert);
            if (curFocus == PointerRoot) curFocus = root;
            XSelectInput(d, curFocus, KeyPressMask|KeyReleaseMask|FocusChangeMask);
            break;

            case KeyPress:
            if(!pressedkeys[ev.xkey.keycode])
                changed[changecount++] = ev.xkey.keycode;
            pressedkeys[ev.xkey.keycode] = true;
            break;

            case KeyRelease:
            if(pressedkeys[ev.xkey.keycode])
                changed[changecount++] = ev.xkey.keycode;
            pressedkeys[ev.xkey.keycode] = false;
            break;
        }
    }
}


InputState::InputState(){
    x=0; y=0; p=0;
    xpercent=0.0;
    ypercent=0.0;
    ppercent=0.0;
    running = true;
    down = false;
    kbthread = new std::thread(&InputState::kbDaemon, this);
}

InputState::~InputState(){
    kbthread->join();
    delete kbthread;
}

void InputState::setState(unsigned char data[12]){
    down = data[1]&1;
    
    x = data[2]+256*data[3];
    y = data[5]+256*data[6];
    p = data[8]+256*data[9];
    
    xpercent = (float)x / MAX_X;
    ypercent = (float)y / MAX_Y;
    ppercent = (float)p / MAX_P;    
}

const unsigned char* InputState::getState(){
    return state;
}
