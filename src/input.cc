#include "input.h"
#include <cstdio>

InputState::InputState(){
    x=0; y=0; p=0;
    xpercent=0.0;
    ypercent=0.0;
    ppercent=0.0;
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
