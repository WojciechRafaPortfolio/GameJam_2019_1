// Created by tomasz on 05.06.19.

#pragma once

#include "Actor.hpp"
#include "Control.hpp"
#include "Animation.hpp"
#include <map>

class AnimationBank : public tt::GlobalActor{
private:
    std::map<sf::String, std::unique_ptr<Animation>> animations;

    bool loadFromFile(Animation& animation, const sf::String& filename);

public:
    Animation& getAnimation(const sf::String& name);

    bool controlActor() override{}
    FUNCTION_GET_TYPE_NAME
};
