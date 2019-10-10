#include <cmath>

#include "profile.h"

BasicProfile::BasicProfile(int rate, float start, float end){
    this->rate = rate;
    this->start = start;
    this->end = end;

    this->i=0.0;
    this->vol=0.0;
    this->voltarget=0.0;
    this->di=0.0;
}


float BasicProfile::getNext(){
    this->i +=di;
    this->i = fmod(this->i, 2*M_PI);
    float dvol = this->voltarget - this->vol;
    this->vol += dvol;
    if(vol>1) vol=1;
    else if(vol<0) vol=0;
    return vol*sin(this->i); 
}

void BasicProfile::onStateUpdate(){
    float freq = start * pow(end/start, state->xpercent);
    di = 2*M_PI*freq/rate;
    voltarget = state->ppercent * state->ppercent;
}
