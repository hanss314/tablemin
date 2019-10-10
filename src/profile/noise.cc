#include <cmath>

#include "profile.h"


float NoiseProfile::getNext(){
    if(!state->down){
        return 0.0;
    }    
    float x = (float)rand()/(float)RAND_MAX;
    x = 2*x-1;
    return state->ppercent*state->ppercent*x; 
}

