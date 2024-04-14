#include "Mario.h"

Mario::Mario():Character(){
};

Mario::Mario(float speed, float max_speed):Character(speed, max_speed)
{
};

std::string Mario::WhatAmI() const{
    return "It's-a Me , Mario" ;
};

Mario::~Mario(){
};