#include <cmath>

#include "profile.h"

float BasicProfile::getNext(){
    this->i +=di;
    this->i = fmod(this->i, 2*M_PI);
    float dvol = this->voltarget - this->vol;
    this->vol += dvol;
    if(vol>1) vol=1;
    else if(vol<0) vol=0;
    return vol*sin(this->i); 
}

void BasicProfile::setState(const unsigned char *data){
    int down = data[1]&1;
    if(!down){
        voltarget = 0.0;
        return;
    }
    
    int x = data[2]+256*data[3];
    //int y = data[5]+256*data[6]
    int p = data[8]+256*data[9];
    
    float xpercent = (float)x / MAX_X;
    float ppercent = (float)p / MAX_P;
    float freq = start * pow(end/start, xpercent);

    di = 2*M_PI*freq/rate;

    voltarget = ppercent*ppercent;
}
