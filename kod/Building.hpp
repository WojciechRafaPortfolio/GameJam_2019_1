// Created by tomasz on 07.06.19.

#pragma once

#include "Actor.hpp"
#include <vector>
#include "ActorPtr.hpp"
#include "Room.hpp"
#include "imconfig.h"
#include "Drawable.hpp"


class Building : public tt::GlobalActor{
private:
    tt::Scene& scene;

    std::vector<std::vector<ActorPtr<Room>>> rooms;

    ActorPtr<RectangleShape> background;

public:
    /// Zwraca pokój, który zawiera w sobie punkt o współrzędnych 'point'
    Room* getRoomByPosition(sf::Vector2f point);

    Room* getRoomByIndex(int x, int y);

    Building();

    ACTOR_NO_CONTROL

};


