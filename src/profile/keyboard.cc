#include <cmath>
#include "profile.h"
    
KeyboardProfile::KeyboardProfile(float *notemap){
    this->notemap = notemap;
    for (int i=0; i<256; i++){
        noteis[i] = 0;
        printf("%f\n", notemap[i]);
        if(notemap[i] != 0.0){
            usednotes[notecount] = i;
            notecount++;
        }
    }
}
KeyboardProfile::~KeyboardProfile(){
    free(notemap);
}

void KeyboardProfile::setRate(int rate){
    Profile::setRate(rate);
    for(int i=0; i<256; i++){
        notemap[i] = notemap[i]*2*M_PI/rate;
    }
}

float KeyboardProfile::getNext() {
    float c = 0.0;
    float s = 0.0;
    for(int i=0; i<notecount; i++){
        int key = usednotes[i];
        noteis[key] += notemap[key];
        if(state->pressedkeys[key]){
            s += sin(noteis[key]);
            c += 1;
        }else{
            noteis[key] = 0.0;
        }
    }
    if(c==0.0){ return 0.0; }
    return s/c;
}

void KeyboardProfile::onKbEvent(int key, bool down){
    //printf("%d %d\n", key, down);
}
