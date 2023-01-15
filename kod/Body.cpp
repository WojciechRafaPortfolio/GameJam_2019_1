// Created by tomasz on 4/15/19.

#include "Body.hpp"
#include "Game.hpp"

Body::Body(const b2BodyDef& definition):
    Parent( scene.getActor<World>().CreateBody( &definition ), &bodyDeleter ){}

Body::~Body(){
    scene.getActor<World>().clearRelatedListeners( get() );
}

// b2Body* Body::operator->(){
//     return get();
// }
//
// b2Body* Body::operator*(){
//     return get();
// }
