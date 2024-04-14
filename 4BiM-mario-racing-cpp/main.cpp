#include <cstdlib>
#include <vector>
#include "Mario.h"
#include "Yoshi.h"

int main(){

    Character perso (5.0,10.0);
    std::cout << perso.WhatAmI() << std::endl;

    Mario mario(7.0,25.0);
    std::cout << mario.WhatAmI() << std::endl;
    std::cout << "Vitesse mario : " << mario.speed() << std::endl ;

    mario.Accelerate();
    std::cout << "Vitesse mario apres acceleration  : " << mario.speed() << std::endl ;
    

    Yoshi yoshi(8.1,40.0, 2);
    std::cout << yoshi.WhatAmI() << std::endl;

    yoshi.set_speed(7.5);
    yoshi.set_max_speed(40.5);
    std::cout << "Vitesse yoshi : " << yoshi.speed() << "  max : " << yoshi.max_speed() << std::endl ;
    yoshi.Accelerate();
    std::cout << "Vitesse yoshi apres acceleration : " << yoshi.speed()  << std::endl ;
    
    std::vector<Character*> racers;

    racers.push_back(&mario);
    racers.push_back(&yoshi);

    racers.push_back(new Mario());
    racers.push_back(new Yoshi());

    for (std::vector<Character*>::iterator it = racers.begin();
        it != racers.end(); ++it){
        (*it)->Accelerate();
        std::cout << "racer : " << (*it)->WhatAmI() << ",  vitesse : " << (*it)->speed() << std::endl ;
    }

    for (auto& racer : racers){
        racer->Accelerate();
        std::cout << "racer : " << racer->WhatAmI() <<  ", vitesse : " << racer->speed() << std::endl ;
    }
    return 0 ;
}