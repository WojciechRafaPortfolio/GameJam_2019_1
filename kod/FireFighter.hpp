//
// Created by Wojtek on 07.06.2019.
//

#ifndef STA_FIREFIGHTER_HPP
#define STA_FIREFIGHTER_HPP

#include "imconfig.h"
#include "Actor.hpp"
#include "Control.hpp"
#include "Drawable.hpp"
#include "Building.hpp"

class FireFighter:public tt::LocalActor
{
public:
    FireFighter();
    ~FireFighter() = default;
    void update();

private:
    void ustaw_punkt_pozycja();
    float up;
    float down;
    float left;
    float right;

    bool ktos_jest_ewakuowany;

    float predkosc_max ;
    sf::Vector2f pozycja;


    ActorPtr <Sprite> Drabina;
    ActorPtr <Sprite> woz_strzazacki;
    ActorPtr <Sprite> Strazak;
    ActorPtr <AAnimatedSprite> gasnica;
    ActorPtr <AAnimatedSprite> pogorzelec;
    float predkosc_pogorzelca ;



    ACTOR_CONTROL(pozycja,predkosc_max)
};


#endif //STA_FIREFIGHTER_HPP
