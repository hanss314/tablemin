#include "profile.h"

ContainerProfile::ContainerProfile(Profile *base){
    this->base = base;
}

ContainerProfile::~ContainerProfile(){
    delete base;
}

void ContainerProfile::setRate(int r){
    Profile::setRate(r);
    base->setRate(r);
}

void ContainerProfile::setInput(InputState *r){
    Profile::setInput(r);
    base->setInput(r);
}

void ContainerProfile::onStateUpdate(){
    base->onStateUpdate();
}

void ContainerProfile::onKbEvent(int key, bool state){
    base->onKbEvent(key, state);
}
