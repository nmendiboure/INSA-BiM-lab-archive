#include "Character.h"

#ifndef YOSHI_H
#define YOSHI_H

class Yoshi : public Character{

    protected:
        int crests_;

    public:
        Yoshi();
        Yoshi(int crests);
        Yoshi(float speed, float max_speed, int crests);
        void set_crests(int new_crests);

        virtual std::string WhatAmI() const override;
        virtual void Accelerate() override ;
    
        inline int crests() const{
            return this->crests_;
        }
        
        ~Yoshi();
};

#endif