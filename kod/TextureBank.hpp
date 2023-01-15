// Created by tomasz on 28.05.19.

#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.hpp"
#include "Control.hpp"


class TextureBank : public tt::GlobalActor{
private:
    std::map<sf::String, std::unique_ptr<sf::Texture>> textures;

public:
    sf::Texture& getTexture(const sf::String& name);

    bool controlActor() override{}
    FUNCTION_GET_TYPE_NAME
};


