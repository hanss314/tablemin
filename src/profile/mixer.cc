#include "profile.h"

MixerProfile::MixerProfile(Profile *a, Profile *b){
    this->a = a;
    this->b = b;
}

MixerProfile::~MixerProfile(){
    delete a;
    delete b;
}

void MixerProfile::setRate(int r){
    Profile::setRate(r);
    a->setRate(r);
    b->setRate(r);
}

void MixerProfile::setInput(InputState *r){
    Profile::setInput(r);
    a->setInput(r);
    b->setInput(r);
}

float MixerProfile::getNext(){
    return a->getNext()*mix + (1-mix)*b->getNext();
}

void MixerProfile::onStateUpdate(){
    a->onStateUpdate();
    b->onStateUpdate();
    mix = state->ypercent;
}

void MixerProfile::onKbEvent(int k, bool s){
    a->onKbEvent(k, s);
    b->onKbEvent(k, s);
}
