#ifndef FUNCS_H
#define FUNCS_H

#include <functional>
#include <cmath>

class WaveformFunc {
    private:
        float (*wave)(float);
    public:
        float period;

    WaveformFunc(float (*wave)(float), float period){
        this->wave = wave;
        this->period = period;
    }

    float call(float *i){
        *i = fmod(*i, period);
        return wave(*i);
    }
};

class ADSRFunc {
    private:
        float (*attdec)(float); float (*release)(float);
    public:
        float attlen, rellen;
    ADSRFunc(float (*init)(float), 
             float (*end)(float), 
             float initlen, float endlen){
        attdec = init;
        release = end;
        attlen = initlen;
        rellen = endlen;
    }

    float getinit(float i){
        if(i>attlen) return 1;
        return attdec(i);
    }

    float getend(float i){
        if(i>rellen) return 0;
        return release(i);
    }
};

float simpleinit(float i);
float simpledecay(float i);
float simplesin(float i);
#endif
