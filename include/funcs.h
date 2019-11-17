#ifndef FUNCS_H
#define FUNCS_H

#include <functional>
#include <cmath>

class WaveformFunc {
    private:
        std::function<float(float)> wave;
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

class AttackFunc {
    private:
        std::function <float(float)> f;
    public:
        float flen;
    AttackFunc(std::function<float(float)> f, float flen){
        this->f = f;
        this->flen = flen;
    }
    float operator()(float i){
        if(i>flen) return 1;
        return f(i);
    }
};

class ReleaseFunc {
    private:
        std::function <float(float)> f;
    public:
        float flen;
    ReleaseFunc(std::function<float(float)> f, float flen){
        this->f = f;
        this->flen = flen;
    }
    float operator()(float i){
        if(i>flen) return 0;
        return f(i);
    }
};

float simpleinit(float i);
float simpledecay(float i);
float simplesin(float i);
#endif
