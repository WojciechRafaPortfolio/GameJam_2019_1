#pragma once

#include <Box2D/Box2D.h>
#include "Caller.hpp"

class DestructionListener : public b2DestructionListener{
public:
    void SayGoodbye(b2Joint* joint) override;

    void SayGoodbye(b2Fixture* fixture) override;
};

class ContactListener : public b2ContactListener{
public:
    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};
