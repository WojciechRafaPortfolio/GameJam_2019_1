// Created by tomasz on 4/15/19.

#pragma once

#include "Body.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class VisibleBody : public Body{
public:
    struct FixtureData{
        b2Fixture& fixture;
        sf::Drawable& graphic;
    };

    VisibleBody();

    explicit VisibleBody(const b2BodyDef& definition);

    FixtureData createFixture(const b2FixtureDef& fixtureDef);

    FixtureData createFixture(const b2Shape& shape, float32 density);

private:
    std::vector<std::unique_ptr<sf::Drawable>> _drawables;

    sf::Drawable& makeGraphicsFromFixture(const b2Fixture& fixture);
};


