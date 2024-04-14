#include "Yoshi.h"

Yoshi::Yoshi():Character(){
    this->crests_= 1;
};

Yoshi::Yoshi(int crests):Character(){
    this->crests_= crests;
};

Yoshi::Yoshi(float speed, float max_speed, int crests = 1):Character(speed, max_speed)
{
    this->crests_= crests;
};

void Yoshi::set_crests(int new_crests){
    this->crests_=new_crests;
};

std::string Yoshi::WhatAmI() const{
    return "It's-a me, Yoshi with " + std::to_string(this->crests_) + " crests";
};

void Yoshi::Accelerate(){
    if (this->speed_ != this->max_speed_){
         this->speed_ += 2;
    }else{
        this->speed_ = this->max_speed_;
    }
};

Yoshi::~Yoshi(){
};