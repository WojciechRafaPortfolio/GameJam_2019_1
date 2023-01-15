// Created by tomasz on 07.06.19.

#pragma once

#include "Actor.hpp"
#include "Control.hpp"
#include "Drawable.hpp"


class Human : public tt::LocalActor{
private:
    ActorPtr<AAnimatedSprite> sprite;

public:
    Human();

    ACTOR_NO_CONTROL
};


