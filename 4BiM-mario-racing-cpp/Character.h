#include<iostream>
#include<string>

#ifndef CHARACTER_H
#define CHARACTER_H

class Character{

    protected:
        // #### Attributs #### //
        float speed_;
        float max_speed_;

    public:

        // #### Constructeurs #### //
        Character() ; 
        Character(float speed, float max_speed);

        void set_speed(float new_speed);
        void set_max_speed(float new_max_speed);


        virtual std::string WhatAmI() const;

        virtual void Accelerate();
        void Break();

        inline float speed() const{
            return this->speed_;
        }

        inline float max_speed() const{
            return this->max_speed_;
        }

        // #### Destructeur #### //
        virtual ~Character();

};

#endif