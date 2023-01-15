#include "WorldCallbacks.hpp"

#include "FixtureData.hpp"

void DestructionListener::SayGoodbye(b2Joint* joint){
    // nothing
}

void DestructionListener::SayGoodbye(b2Fixture* fixture){
    getFixtureData( fixture ).callerFixtureDestruction.call( std::move(fixture) );
    delete &getFixtureData( fixture );
}


void ContactListener::BeginContact(b2Contact* contact){
    getFixtureData( contact->GetFixtureA() ).callerBeginContact.call( std::move(contact) );
    getFixtureData( contact->GetFixtureB() ).callerBeginContact.call( std::move(contact) );
}

void ContactListener::EndContact(b2Contact* contact){
    getFixtureData( contact->GetFixtureA() ).callerEndContact.call( std::move(contact) );
    getFixtureData( contact->GetFixtureB() ).callerEndContact.call( std::move(contact) );
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold){
    getFixtureData( contact->GetFixtureA() ).callerPreSolve.call( std::move(contact), std::move(oldManifold) );
    getFixtureData( contact->GetFixtureB() ).callerPreSolve.call( std::move(contact), std::move(oldManifold) );
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){
    getFixtureData( contact->GetFixtureA() ).callerPostSolve.call( std::move(contact), std::move(impulse) );
    getFixtureData( contact->GetFixtureB() ).callerPostSolve.call( std::move(contact), std::move(impulse) );
}
