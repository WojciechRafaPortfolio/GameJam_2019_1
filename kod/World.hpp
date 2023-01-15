// Created by tomasz on 16.05.19.

#pragma once

#include <Box2D/Box2D.h>
#include "Actor.hpp"
#include "Caller.hpp"
#include <map>
#include "Control.hpp"

class World : public tt::LocalActor, public b2World{
private:
    class Box2dDestructionListener : public b2DestructionListener{
        World& world;
    public:
        explicit Box2dDestructionListener(World& world);
        void SayGoodbye(b2Joint* joint) override;
        void SayGoodbye(b2Fixture* fixture) override;
    };

    class Box2dContactListener : public b2ContactListener{
        World& world;
    public:
        explicit Box2dContactListener(World& world);
        void BeginContact(b2Contact* contact) override;
        void EndContact(b2Contact* contact) override;
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
    };

    Box2dDestructionListener destructionListener;
    Box2dContactListener contactListener;

    // body
    std::map<b2Body*, Caller<b2Contact*>> callersBodyBeginContact;
    std::map<b2Body*, Caller<b2Contact*>> callersBodyEndContact;
    std::map<b2Body*, Caller<b2Contact*, const b2Manifold*>> callersBodyPreSolve;
    std::map<b2Body*, Caller<b2Contact*, const b2ContactImpulse*>> callersBodyPostSolve;

    // fixture
    std::map<b2Fixture*, Caller<b2Contact*>> callersFixtureBeginContact;
    std::map<b2Fixture*, Caller<b2Contact*>> callersFixtureEndContact;
    std::map<b2Fixture*, Caller<b2Contact*, const b2Manifold*>> callersFixturePreSolve;
    std::map<b2Fixture*, Caller<b2Contact*, const b2ContactImpulse*>> callersFixturePostSolve;
    std::map<b2Fixture*, Caller<>> callersFixtureDelete;

    template <typename T>
    using FuncRefType = typename T::value_type::second_type::FuncRefType;

public:
    // body
    using BodyBeginContactFunctionRef = FuncRefType<decltype( callersBodyBeginContact )>;
    using BodyEndContactFunctionRef = FuncRefType<decltype( callersBodyEndContact )>;
    using BodyPreSolveFunctionRef = FuncRefType<decltype( callersBodyPreSolve )>;
    using BodyPostSolveFunctionRef = FuncRefType<decltype( callersBodyPostSolve )>;

    // fixture
    using FixtureBeginContactFunctionRef = FuncRefType<decltype( callersFixtureBeginContact )>;
    using FixtureEndContactFunctionRef = FuncRefType<decltype( callersFixtureEndContact )>;
    using FixturePreSolveFunctionRef = FuncRefType<decltype( callersFixturePreSolve )>;
    using FixturePostSolveFunctionRef = FuncRefType<decltype( callersFixturePostSolve )>;
    using FixtureDeleteFunctionRef = FuncRefType<decltype( callersFixtureDelete )>;

    Observer onBodyBeginContact(b2Body*, BodyBeginContactFunctionRef);
    Observer onBodyEndContact(b2Body*, BodyEndContactFunctionRef);
    Observer onBodyPreSolve(b2Body*, BodyPreSolveFunctionRef);
    Observer onBodyPostSolve(b2Body*, BodyPostSolveFunctionRef);

    Observer onFixtureBeginContact(b2Fixture*, FixtureBeginContactFunctionRef);
    Observer onFixtureEndContact(b2Fixture*, FixtureEndContactFunctionRef);
    Observer onFixturePreSolve(b2Fixture*, FixturePreSolveFunctionRef);
    Observer onFixturePostSolve(b2Fixture*, FixturePostSolveFunctionRef);
    Observer onFixtureDelete(b2Fixture*, FixtureDeleteFunctionRef);

    World();

    void clearRelatedListeners(b2Body*);
    void clearRelatedListeners(b2Fixture*);

    bool controlActor() override{}
    FUNCTION_GET_TYPE_NAME
};
