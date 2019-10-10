#include "profile.h"
#include "input.h"
#include <cstdio>

void Profile::setRate(int r){
    rate = r;
}

void Profile::setInput(InputState *s){
    state = s;
}
