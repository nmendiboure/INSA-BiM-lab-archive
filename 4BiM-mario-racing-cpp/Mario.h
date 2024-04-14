#include "Character.h"

#ifndef MARIO_H
#define MARIO_H

class Mario : public Character{
    public:
        Mario();
        Mario(float speed, float max_speed);
        virtual std::string WhatAmI() const override ;

        ~Mario();
};

#endif