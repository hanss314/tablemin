#include "input.h"

#ifndef PROFILE_H
#define PROFILE_H

class Profile{
    protected:
        int rate;
        InputState *state;

    public:
    virtual float getNext(){ return 0; };
    virtual ~Profile() {};

    virtual void setRate(int);
    virtual void setInput(InputState *input);
    virtual void onStateUpdate(){};
};

class BasicProfile : public Profile{
    protected:
       float i, start, end, vol, voltarget, di;

    public:     
    BasicProfile(int rate, float start, float end);
    float getNext() override;
    void onStateUpdate() override;
};

//class TimbreProfile : public Profile{};
class ExtratoneProfile : public Profile{
    protected:
        float i, start, end, di;
        Profile *base;

    public:
    ExtratoneProfile(Profile *base, float start, float end);
    ~ExtratoneProfile();
    float getNext() override;

    void setRate(int) override;
    void setInput(InputState *input) override;
    void onStateUpdate() override;
};


class NoiseProfile : public Profile{
    public:
    float getNext() override;
};

#endif
