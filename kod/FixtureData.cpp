#include "FixtureData.hpp"

FixtureData& getFixtureData(b2Fixture* fixture){
    auto* fixtureData = reinterpret_cast<FixtureData*>( fixture->GetUserData() );
    if( fixtureData == nullptr ){
        fixtureData = new FixtureData;
        fixture->SetUserData( fixtureData );
    }
    return *fixtureData;
}
