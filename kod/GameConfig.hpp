// Created by tomasz on 4/17/19.

#pragma once

#include "Config.hpp"
#include <Box2D/Box2D.h>

class GameConfig : public Config{
public:
    GameConfig(const std::string& filename);

    /** name Should contain path to block containing:
     * block shape (see getShape())
     * float friction
     * float restitution
     * float density
     * bool isSensor
     */
    std::unique_ptr<b2FixtureDef> getFixtureDef(const std::string& name);

    /** name Should contain path to block containing:
     *     string type
     * if type == "polygon":
     *    int count <- count of verticles
     *    and block named 0, 1, 2, ect. to count-1 containing:
     *        float x
     *        float y
     * if type == "circle"
     *    float radius
    */
    std::unique_ptr<b2Shape> getShape(const std::string& name);

    /** name Should contain path to block containing:
     * block position
     *     float x
     *     float y
     * float angle
     * block linearVelocity
     *     float x
     *     float y
     * float angularVelocity
     * float linearDamping
     * float angularDamping
     * bool allowSleep
     * bool awake
     * bool fixedRotation
     * bool bullet
     * bool active
     * float gravityScale
     * string type ("static", "kinematic", "dynamic")
     * block fixtures
     *     int count <- count of fixtures
     *     block 0 // 1, 2, etc. to count-1
     *         see getFixtureDef
    */
    std::unique_ptr<b2BodyDef> getBodyDef(const std::string& name);
};


