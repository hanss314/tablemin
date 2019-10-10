#define MAX_X 15200
#define MAX_Y 9500
#define MAX_P 4095

#ifndef INPUT_H
#define INPUT_H

class InputState {
    protected:
    unsigned char state[12];
    
    public:
    bool down;
    int x, y, p;
    float xpercent, ypercent, ppercent;
    InputState();
    void setState(unsigned char state[12]);
    const unsigned char* getState();
};

#endif
