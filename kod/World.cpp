// Created by tomasz on 16.05.19.

#include "World.hpp"

World::World():
    destructionListener( *this ),
    contactListener( *this ),
    b2World( {0, 0} ){
    SetDestructionListener( &destructionListener );
    SetContactListener( &contactListener );
}

World::Box2dContactListener::Box2dContactListener(World& world):
    world( world ){}

World::Box2dDestructionListener::Box2dDestructionListener(World& world):
    world( world ){}

void World::Box2dContactListener::BeginContact(b2Contact* contact){
    auto fixtureA = contact->GetFixtureA();
    world.callersBodyBeginContact[fixtureA->GetBody()].call( std::move(contact) );
    world.callersFixtureBeginContact[fixtureA].call( std::move(contact) );
    auto fixtureB = contact->GetFixtureB();
    world.callersBodyBeginContact[fixtureB->GetBody()].call( std::move(contact) );
    world.callersFixtureBeginContact[fixtureB].call( std::move(contact) );
}

void World::Box2dContactListener::EndContact(b2Contact* contact){
    auto fixtureA = contact->GetFixtureA();
    world.callersBodyEndContact[fixtureA->GetBody()].call( std::move(contact) );
    world.callersFixtureEndContact[fixtureA].call( std::move(contact) );
    auto fixtureB = contact->GetFixtureB();
    world.callersBodyEndContact[fixtureB->GetBody()].call( std::move(contact) );
    world.callersFixtureEndContact[fixtureB].call( std::move(contact) );
}

void World::Box2dContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
    auto fixtureA = contact->GetFixtureA();
    world.callersBodyPreSolve[fixtureA->GetBody()].call( std::move(contact), std::move(oldManifold) );
    world.callersFixturePreSolve[fixtureA].call( std::move(contact), std::move(oldManifold) );
    auto fixtureB = contact->GetFixtureB();
    world.callersBodyPreSolve[fixtureB->GetBody()].call( std::move(contact), std::move(oldManifold) );
    world.callersFixturePreSolve[fixtureB].call( std::move(contact), std::move(oldManifold) );
}

void World::Box2dContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
    auto fixtureA = contact->GetFixtureA();
    world.callersBodyPostSolve[fixtureA->GetBody()].call( std::move(contact), std::move(impulse) );
    world.callersFixturePostSolve[fixtureA].call( std::move(contact), std::move(impulse) );
    auto fixtureB = contact->GetFixtureB();
    world.callersBodyPostSolve[fixtureB->GetBody()].call( std::move(contact), std::move(impulse) );
    world.callersFixturePostSolve[fixtureB].call( std::move(contact), std::move(impulse) );
}

void World::Box2dDestructionListener::SayGoodbye(b2Fixture* fixture){
    world.callersFixtureDelete[fixture].call();
}

void World::Box2dDestructionListener::SayGoodbye(b2Joint* joint){
    // TODO
}

Observer World::onBodyBeginContact(b2Body* body, World::FuncRefType<decltype( callersBodyBeginContact )> func){
    return callersBodyBeginContact[body].createObserver( func );
}

Observer World::onBodyEndContact(b2Body* body, World::FuncRefType<decltype( callersBodyEndContact )> func){
    return callersBodyEndContact[body].createObserver( func );
}

Observer World::onBodyPreSolve(b2Body* body, World::FuncRefType<decltype( callersBodyPreSolve )> func){
    return callersBodyPreSolve[body].createObserver( func );
}

Observer World::onBodyPostSolve(b2Body* body, World::FuncRefType<decltype( callersBodyPostSolve )> func){
    return callersBodyPostSolve[body].createObserver( func );
}

Observer World::onFixtureBeginContact(b2Fixture* fixture, World::FuncRefType<decltype( callersFixtureBeginContact )> func){
    return callersFixtureBeginContact[fixture].createObserver( func );
}

Observer World::onFixtureEndContact(b2Fixture* fixture, World::FuncRefType<decltype( callersFixtureEndContact )> func){
    return callersFixtureEndContact[fixture].createObserver( func );
}

Observer World::onFixturePreSolve(b2Fixture* fixture, World::FuncRefType<decltype( callersFixturePreSolve )> func){
    return callersFixturePreSolve[fixture].createObserver( func );
}

Observer World::onFixturePostSolve(b2Fixture* fixture, World::FuncRefType<decltype( callersFixturePostSolve )> func){
    return callersFixturePostSolve[fixture].createObserver( func );
}

Observer World::onFixtureDelete(b2Fixture* fixture, World::FuncRefType<decltype( callersFixtureDelete )> func){
    return callersFixtureDelete[fixture].createObserver( func );
}

void World::clearRelatedListeners(b2Body* body){
    callersBodyBeginContact.erase(body);
    callersBodyEndContact.erase(body);
    callersBodyPreSolve.erase(body);
    callersBodyPostSolve.erase(body);

    for(auto fixture=body->GetFixtureList(); fixture; fixture=fixture->GetNext())
        clearRelatedListeners(fixture);
}

void World::clearRelatedListeners(b2Fixture* fixture){
    callersFixtureBeginContact.erase(fixture);
    callersFixtureEndContact.erase(fixture);
    callersFixturePreSolve.erase(fixture);
    callersFixturePostSolve.erase(fixture);
}
