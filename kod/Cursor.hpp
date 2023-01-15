//
// Created by Wojtek on 07.06.2019.
//

#ifndef STA_CURSOR_HPP
#define STA_CURSOR_HPP

#include "Actor.hpp"
#include "Control.hpp"
#include "Drawable.hpp"

class Cursor: public  tt::LocalActor
{
public:
    Cursor();
    ~Cursor() = default;
    void up_date();
private:
    ActorPtr <AAnimatedSprite> plomyk;
    int ilosc_obiegow_max ;

    ACTOR_CONTROL(ilosc_obiegow_max);
};

#endif //STA_CURSOR_HPP
