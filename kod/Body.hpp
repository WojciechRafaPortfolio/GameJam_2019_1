// Created by tomasz on 4/15/19.

#pragma once

#include <memory>
#include <Box2D/Box2D.h>
#include "World.hpp"
#include "Actor.hpp"
#include "Scene.hpp"

inline void bodyDeleter(b2Body* ptr){
    ptr->GetWorld()->DestroyBody( ptr );
}

namespace{
using Parent = std::unique_ptr<b2Body, decltype( &bodyDeleter )>;
}

class Body : public tt::LocalActor, public Parent{
private:
    using Parent = ::Parent;

public:
    explicit Body(const b2BodyDef& definition);

    ~Body() override;

    Observer onBeginContact(World::BodyBeginContactFunctionRef func){
        return scene.getActor<World>().onBodyBeginContact( get(), func );
    }

    Observer onEndContact(World::BodyEndContactFunctionRef func){
        return scene.getActor<World>().onBodyEndContact( get(), func );
    }

    Observer onPreSolve(World::BodyPreSolveFunctionRef func){
        return scene.getActor<World>().onBodyPreSolve( get(), func );
    }

    Observer onPostSolve(World::BodyPostSolveFunctionRef func){
        return scene.getActor<World>().onBodyPostSolve( get(), func );
    }

    //b2Body* operator->();
    //b2Body* operator*();
    bool controlActor() override{}
    FUNCTION_GET_TYPE_NAME
};


