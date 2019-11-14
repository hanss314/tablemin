#include <cmath>
#include <cstdio>

#include "profile.h"
#include "input.h"

EnablerProfile::
EnablerProfile(Profile *base, int key)
:ContainerProfile(base){
    enablekey = key;
}

float EnablerProfile::getNext(){
    if(!state->pressedkeys[enablekey]) return 0;
    return base->getNext();
}


MuterProfile::
MuterProfile(Profile *base, int key)
:ContainerProfile(base){
    mutekey = key;
}

float MuterProfile::getNext(){
    if(state->pressedkeys[mutekey]) return 0;
    return base->getNext();
}

