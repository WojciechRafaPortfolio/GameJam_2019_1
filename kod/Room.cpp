// Created by tomasz on 07.06.19.

#include "Room.hpp"
#include "Scene.hpp"
#include "Building.hpp"
#include "Layers.hpp"
#include "TextureBank.hpp"
#include "AConfig.hpp"
#include "AnimationBank.hpp"

float Room::getFire() const{
    return fire;
}

float Room::getSmoke() const{
    return smoke;
}

Room::Room(int x, int y, const sf::Vector2f& position):
    x( x ),
    y( y ),
    fire( 0 ),
    smoke( 0 ),
    sInside( scene.createActor<Sprite>( e_roomBackground ) ),
    sGlass( scene.createActor<Sprite>( e_glass ) ),
    sWall( scene.createActor<Sprite>( e_wall ) ),
    sFire( scene.createActor<AAnimatedSprite>( e_fire ) ),
    sSmoke( scene.createActor<AAnimatedSprite>( e_smoke ) ),
    doEveryFrame(
        scene.onEveryStep(
            [this](){
                if( fire > 0 ){
                    if( smoke > 0 )
                        fire--;
                    else if( fire < 100 )
                        fire += scene.getActor<RoomCommon>().fireSpeed;
                    auto* topRoom = scene.getActor<Building>().getRoomByIndex( this->x, 0 );
                    assert( topRoom );
                    topRoom->makeSmoke( scene.getActor<RoomCommon>().smokeSpeed );
                }
                sFire->setScale( 1, fire / 100.f );
                sSmoke->setScale( 1, smoke / 100.f );
            }
        )
    ){
    auto configG = scene.getActor<AConfig>().getConfig( "Graphics.txt" );
    sGlass->setTexture(
        scene.getActor<TextureBank>()
             .getTexture( "Grafiki/png/szyba.png" )
    );
    sInside->setTexture(
        scene.getActor<TextureBank>()
             .getTexture(
                 "Grafiki/png/pokoj" +
                 std::to_string( (std::rand() % 9) + 1 )
             )
    );
    sWall->setTexture(
        scene.getActor<TextureBank>()
             .getTexture(
                 "Grafiki/png/sciana" +
                 std::to_string( (std::rand() % 8) + 1 )
             )
    );
    sFire->setAnimation(
        scene.getActor<AnimationBank>()
             .getAnimation( "Grafiki/animacja/ogien.txt" )
    );
    sSmoke->setAnimation(
        scene.getActor<AnimationBank>()
             .getAnimation( "Grafiki/animacja/smoke.txt" )
    );
    sInside->setPosition( position );
    sWall->setPosition( position );
    sFire->setPosition( position );
    sSmoke->setPosition( position );
    sGlass->setPosition(
        (position.x + sInside->getTexture()->getSize().x / 2.f - sGlass->getTexture()->getSize().x / 2.f),
        (position.y + sInside->getTexture()->getSize().y / 2.f - sGlass->getTexture()->getSize().y / 2.f)
    );
}

void Room::makeSmoke(float addtionalSmoke){
    if( smoke < 100 ){
        smoke += addtionalSmoke;
    }else{
        auto* roomBelow = scene.getActor<Building>().getRoomByIndex( x, y + 1 );
        if( roomBelow )
            roomBelow->makeSmoke( scene.getActor<RoomCommon>().smokeSpeed );
    }
}

sf::Vector2f Room::getSize(){
    auto size = sInside->getTexture()->getSize();
    return sf::Vector2f( size.x, size.y );
}

bool Room::isPointInWindow(const sf::Vector2f& point){
    Config config( "Building" );
    sf::Vector2f windowShift(
        config.get<int>( "windowShift.x" ),
        config.get<int>( "windowShift.y" )
    );
    sf::Vector2f windowSize(
        config.get<int>( "windowSize.x" ),
        config.get<int>( "windowSize.y" )
    );

    if( sInside->getPosition().x + windowShift.x > point.x
        || point.x > sInside->getPosition().x + windowShift.x + windowSize.x
        || sInside->getPosition().y + windowShift.y > point.y
        || point.y > sInside->getPosition().y + windowShift.y + windowSize.y )
        return false;
    return true;
}

void Room::breakWindow(){
    window = false;
    sGlass->setTexture(
        scene.getActor<TextureBank>()
             .getTexture(
                 "Grafiki/png/zbita" +
                 std::to_string( (std::rand() % 4) + 1 )
             )
    );
}

void Room::killFire(){
    fire -= scene.getActor<RoomCommon>().fireKilling;
    if( fire < 0 )
        fire = 0;
}

void Room::saveHuman(){
    if( ifIsSomeone() )
        humans.pop_back();
}

bool Room::ifIsSomeone(){
    return !humans.empty();
}

void Room::start_fire(){
    if( fire < scene.getActor<RoomCommon>().startFire )
        fire = scene.getActor<RoomCommon>().startFire;
}

bool Room::isPointInRoom(sf::Vector2f point){
    if( sInside->getPosition().x > point.x
        || point.x > sInside->getPosition().x + sInside->getTexture()->getSize().x
        || sInside->getPosition().y > point.y
        || point.y > sInside->getPosition().y + sInside->getTexture()->getSize().y )
        return false;
    return true;
}

RoomCommon::RoomCommon(){
    Config config( "Building" );
    fireSpeed = config.get<float>( "fireSpeed" );
    smokeSpeed = config.get<float>( "smokeSpeed" );
    fireDumping = config.get<float>( "fireDumping" );
    startFire = config.get<float>( "startFire" );
    fireKilling = config.get<float>( "fireKilling" );
}
