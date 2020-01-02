#include <cmath>
#include <cstdio>

#include "funcs.h"

float __simpleattack(float i){
    if(i<1.0/1000.0) return 1200*i;
    else return 1.2-1000*(i-1.0/1000.0);
}

float __simpledecay(float i){
    return 1.0-10*i;
}

float __simplesin(float i){
    return sin(i);
}

float __triangle(float i){
    return i-1;
}

float __square(float i){
    if(i<1) return -1;
    else return 1;
}

AttackFunc simpleattack(__simpleattack, 1.2/1000.0);
ReleaseFunc simplerelease(__simpledecay, 1.0/10.0);
WaveformFunc simplesin(__square, 2);
