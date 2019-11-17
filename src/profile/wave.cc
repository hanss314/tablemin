#include <cmath>

#include "profile.h"

WaveProfile::WaveProfile(float start, float end, 
                         WaveformFunc *wave, ADSRFunc *adsr){
    this->start = start;
    this->end = end;
    this->wave = wave;
    this->adsr = adsr;

    this->play = false;
    this->i=0.0;
    this->vol=0.0;
    this->di=0.0;
    this->notetimer=0.0;
    this->reltimer=0.0;
           

}

float WaveProfile::getNext(){
    if(!play) return 0.0;
    this->i +=di;
    float w = wave->call(&(this->i));
    float a = 1.0;
    if(state->down){
        notetimer += 1.0/rate;
        if(notetimer<adsr->attlen) a=adsr->getinit(notetimer);
    } else {
        reltimer += 1.0/rate;
        if(reltimer>adsr->rellen){
            play = false; return 0;
        }
        a=adsr->getend(reltimer);
    }
    return a*w;
}

void WaveProfile::onStateUpdate(){
    if(state->down){
        play = true;
        reltimer=0.0;
    } else {
        notetimer=0.0;
    }
    float freq = start * pow(end/start, state->xpercent);
    di = (wave->period)*freq/rate;
    //vol = state->ppercent * state->ppercent;
}
