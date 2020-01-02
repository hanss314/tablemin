#include <cmath>
#include <cstdio>

#include "profile.h"
#include "input.h"

LooperProfile::
LooperProfile(Profile *base, int key, size_t length)
:ContainerProfile(base){
    loopkey = key;
    loop_pos = 0;
    loop_len = 0;
    buf_size = length;
    looping = false;
    loop = (float*)malloc(sizeof(float)*length);
}

LooperProfile::
~LooperProfile(){
    free(loop);
}

float LooperProfile::getNext(){
    if(looping){
        loop_pos %= loop_len;
        return loop[loop_pos++];
    }
    float x = base->getNext();
    loop_len = loop_len < loop_pos ? loop_pos : loop_len;
    loop_pos %= buf_size;
    loop[loop_pos++] = x;
    return x;
}

void LooperProfile::onKbEvent(int key, bool down){
    if(key!=loopkey || !down) return;
    looping = !looping;
    loop_pos = 0;
    if(!looping){
        loop_len = 0;    
    }
    printf("%d\n", looping);
}
