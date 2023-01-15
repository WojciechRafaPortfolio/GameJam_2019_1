// Created by tomasz on 28.05.19.

#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.hpp"
#include "Control.hpp"


class FontBank : public tt::GlobalActor{
private:
    std::map<sf::String, std::unique_ptr<sf::Font>> fonts;

public:
    sf::Font& getFont(const sf::String& name);

    bool controlActor() override{}
    FUNCTION_GET_TYPE_NAME
};


