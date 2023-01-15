#pragma once

#include <Box2D/Box2D.h>
#include "Caller.hpp"

struct FixtureData{
    Caller<b2Contact*> callerBeginContact;
    Caller<b2Contact*> callerEndContact;
    Caller<b2Contact*, const b2Manifold*> callerPreSolve;
    Caller<b2Contact*, const b2ContactImpulse*> callerPostSolve;
    Caller<b2Fixture*> callerFixtureDestruction;
};

FixtureData& getFixtureData(b2Fixture*);
