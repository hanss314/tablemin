#include <cmath>
#include <cstdio>

#include "profile.h"
#include "input.h"

ExtratoneProfile::
ExtratoneProfile(Profile *base, float start, float end)
:ContainerProfile(base){
    this->start = start;
    this->end = end;
    this->base = base;

    this->i=0.0;
    this->di=0.0;
}


float ExtratoneProfile::getNext(){
    this->i+=di;
    this->i = fmod(this->i, 2*M_PI);
    if(i<M_PI) return 0;
    return base->getNext();
}

void ExtratoneProfile::onStateUpdate(){
    if(state->ypercent > 0.95){
        di=0;
        this->i=M_PI;
    }
    float freq = start * pow(end/start, 1-state->ypercent);
    di = 2*M_PI*freq;
    di /= (float)rate;
    ContainerProfile::onStateUpdate();
}
