#include <cmath>
#include <cstdio>

#include "profile.h"
#include "input.h"

ExtratoneProfile::
ExtratoneProfile(Profile *base, float start, float end){
    this->start = start;
    this->end = end;
    this->base = base;

    this->i=0.0;
    this->di=0.0;
}
ExtratoneProfile::~ExtratoneProfile(){
    delete base;
}


float ExtratoneProfile::getNext(){
    this->i+=di;
    this->i = fmod(this->i, 2*M_PI);
    if(i<M_PI) return 0;
    return base->getNext();
}

void ExtratoneProfile::setRate(int r){
    Profile::setRate(r);
    base->setRate(r);
}


void ExtratoneProfile::setInput(InputState *r){
    Profile::setInput(r);
    base->setInput(r);
}

void ExtratoneProfile::onStateUpdate(){
    float freq = start * pow(end/start, 1-state->ypercent);
    di = 2*M_PI*freq;
    di /= (float)rate;
    base->onStateUpdate();
}
