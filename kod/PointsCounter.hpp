//
// Created by Wojtek on 08.06.2019.
//

#ifndef STA_POINTSCOUNTER_HPP
#define STA_POINTSCOUNTER_HPP

#include "Actor.hpp"
#include "Control.hpp"
#include "Drawable.hpp"

class PointsCounter: public tt::GlobalActor
{
public:
    PointsCounter();
    ~PointsCounter() = default;
void humanDied();
void humanSave();

void update();

private:
int liczba_zgonow;
int liczba_ocalonych;

ActorPtr <Text> ocaleni_tekst;
ActorPtr <Text> zgony_tekst;

};

#endif //STA_POINTSCOUNTER_HPP
