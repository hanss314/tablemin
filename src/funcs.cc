#include <cmath>
#include <cstdio>

float simpleinit(float i){
    if(i<1.0/1000.0) return 1200*i;
    else return 1.2-1000*(i-1.0/1000.0);
}

float simpledecay(float i){
    return 1.0-10*i;
}

float simplesin(float i){
    return sin(i);
}
