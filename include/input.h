#ifndef INPUT_H
#define INPUT_H

#include <thread>

#define MAX_X 15200
#define MAX_Y 9500
#define MAX_P 4095

class InputState {
    protected:
    unsigned char state[12];
    bool running;
    std::thread *kbthread;

    public:
    bool down;
    int x, y, p;
    float xpercent, ypercent, ppercent;
    bool pressedkeys[256];
    int changed[256];
    int changecount = 0;

    InputState();
    ~InputState();
    void setState(unsigned char state[12]);
    const unsigned char* getState();
    void kbDaemon();
};

#endif
