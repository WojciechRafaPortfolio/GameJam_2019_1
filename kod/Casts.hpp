#pragma once

#include <SFML/System/Vector2.hpp>
#include <Box2D/Common/b2Math.h>

inline sf::Vector2f vector(const b2Vec2& vec){
    return {vec.x, vec.y};
}

inline b2Vec2 vector(const sf::Vector2f& vec){
    return {vec.x, vec.y};
}

inline float degToRad(float deg){
    return deg * M_PI / 180.f;
}

inline float radToDeg(float rad){
    return rad / M_PI * 180.f;
}
