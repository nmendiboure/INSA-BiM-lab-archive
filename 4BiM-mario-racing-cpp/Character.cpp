#include "Character.h"

Character::Character(){
    this->speed_ = 0;
    this->max_speed_ = 10;
};

Character::Character(float speed, float max_speed){
    this->speed_ = speed;
    this->max_speed_ = max_speed;
};

void Character::set_speed(float new_speed){
    this->speed_ = new_speed;
};

void Character::set_max_speed(float new_max_speed){
    this->max_speed_ = new_max_speed;
};

void Character::Accelerate(){
    if (this->speed_ != this->max_speed_){
         this->speed_ +=1;
    }else{
        this->speed_ = this->max_speed_;
    }
};

void Character::Break(){
    if (this->speed_ > 0){
         this->speed_ -=1;
    }else{
        this->speed_ = 0;
    }
};

std::string Character::WhatAmI() const{
    return "A character has no name";
};

Character::~Character(){
};