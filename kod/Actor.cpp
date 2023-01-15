// Created by tomasz on 19.05.19.

#include "Actor.hpp"
#include "Scene.hpp"

namespace tt{

unsigned Actor::topId;

LocalActor::LocalActor():
    scene( tt::Scene::getCreator() ){}

LocalActor::LocalActor(const std::string& name):
    Actor( name ),
    scene( tt::Scene::getCreator() ){}

void LocalActor::destroy(){
    scene.destroyActor( *this );
}

GlobalScene& LocalActor::getGlogalScene(){
    return scene;
}

GlobalActor::GlobalActor():
    globalScene( GlobalScene::getCreator() ){}

GlobalActor::GlobalActor(const std::string& name):
    Actor( name ),
    globalScene( GlobalScene::getCreator() ){}

Actor::Actor(const std::string& name):
    id( ++topId ),
    name( name ),
    opened( false ){}

void Actor::switchOpened(){
    opened = !opened;
};

bool Actor::isOpened() const{
    return opened;
}

const std::string& Actor::getName(){
    if( name.empty() )
        name = "NoName_" + getTypeName() + '_' + std::to_string( id );
    return name;
};
}
