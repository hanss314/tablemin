#ifndef PROFILE_H
#define PROFILE_H

#include "input.h"
#include "funcs.h"

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
    virtual void onKbEvent(int key, bool down){};
};

class BasicProfile : public Profile{
    protected:
       float i, start, end, vol, voltarget, di;

    public:     
    BasicProfile(float start, float end);
    float getNext() override;
    void onStateUpdate() override;
};

class WaveProfile : public Profile{
    protected:
       bool play;
       float i, start, end, vol, voltarget, di, reltimer, notetimer;
       WaveformFunc *wave;
       AttackFunc *att;
       ReleaseFunc *rel;

    public:     
    WaveProfile(float start, float end, 
                WaveformFunc *wave, AttackFunc *att, ReleaseFunc *rel);
    float getNext() override;
    void onStateUpdate() override;
};

class KeyboardProfile : public Profile{
    protected:
        float *notemap;
        int notecount;
        int usednotes[256];
        float noteis[256];
        

    public:     
    KeyboardProfile(float *notemap);
    ~KeyboardProfile();

    float getNext() override;
    void onKbEvent(int, bool) override;
    void setRate(int) override;
};

class MixerProfile : public Profile{
    protected:
        Profile *a;
        Profile *b;
        float mix;
    public:
    MixerProfile(Profile *a, Profile *b);
    ~MixerProfile();

    float getNext() override;
    void setRate(int) override;
    void setInput(InputState *input) override;
    void onStateUpdate() override;
    void onKbEvent(int, bool) override;
};

//class TimbreProfile : public Profile{};
class NoiseProfile : public Profile{
    public:
    float getNext() override;
};

class DiscreteProfile : public Profile{
    protected:
       float i, start, end, vol, voltarget, di;
       int quanta; 

    public:     
    DiscreteProfile(float start, float end);
    float getNext() override;
    void onStateUpdate() override;
};

class ContainerProfile : public Profile{
    protected:
        Profile *base;
    ContainerProfile(Profile *base);
    ~ContainerProfile();

    void onKbEvent(int, bool) override;
    void setRate(int) override;
    void setInput(InputState *input) override;
    void onStateUpdate() override;
};

class ExtratoneProfile : public ContainerProfile{
    protected:
        float i, start, end, di;

    public:
    ExtratoneProfile(Profile *base, float start, float end);
    float getNext() override;
    void onStateUpdate() override;
};

class EnablerProfile : public ContainerProfile{
    protected:
        int enablekey;

    public:
    EnablerProfile(Profile *base, int key);
    float getNext() override;
};
class MuterProfile : public ContainerProfile{
    protected:
        int mutekey;

    public:
    MuterProfile(Profile *base, int key);
    float getNext() override;
};
class LooperProfile : public ContainerProfile{
    protected:
        int loopkey;
        size_t loop_pos, buf_size, loop_len;
        float *loop;
        bool looping;
        
    public:
    LooperProfile(Profile *base, int key, size_t length);
    ~LooperProfile();
    float getNext() override;
    void onKbEvent(int, bool) override;
};
#endif
