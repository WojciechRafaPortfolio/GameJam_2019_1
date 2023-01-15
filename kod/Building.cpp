// Created by tomasz on 07.06.19.

#include "Building.hpp"
#include "Layers.hpp"
#include "TextureBank.hpp"
#include "AConfig.hpp"

Building::Building():
    GlobalActor( "Building" ),
    scene( dynamic_cast<tt::Scene&>(getGlogalScene()) ),
    background( scene.createActor<RectangleShape>( e_background ) ){
    Config config( "Building" );
    auto roomsCountX = config.get<int>( "roomsCount.x" );
    auto roomsCountY = config.get<int>( "roomsCount.y" );
    sf::Vector2f spaceBetweenRooms(
        config.get<float>( "spaceBetweenRooms.x" ),
        config.get<float>( "spaceBetweenRooms.y" )
    );
    auto& roomTexture = scene.getActor<TextureBank>()
                             .getTexture( "Grafiki/png/pokoj1.png" );
    sf::Vector2f roomSize(
        roomTexture.getSize().x,
        roomTexture.getSize().y
    );

    for(auto x = 0; x < roomsCountX; x++){
        rooms.emplace_back();
        for(auto y = 0; y < roomsCountY; y++){
            sf::Vector2f roomPos(
                spaceBetweenRooms.x + x * (roomSize.x + spaceBetweenRooms.x),
                spaceBetweenRooms.y + y * (roomSize.y + spaceBetweenRooms.y)
            );
            rooms.back().emplace_back( scene.createActor<Room>( x, y, roomPos ) );
        }
    }

    sf::Vector2f backgroundSize(
        roomsCountX * (roomSize.x + spaceBetweenRooms.x) + spaceBetweenRooms.x,
        roomsCountY * (roomSize.y + spaceBetweenRooms.y) + spaceBetweenRooms.y
    );
    background->setSize( roomSize + spaceBetweenRooms );
}

Room* Building::getRoomByIndex(int x, int y){
    if( rooms.size() < x || rooms[x].size() < y )
        return nullptr;
    return rooms[x][y];
}

Room* Building::getRoomByPosition(sf::Vector2f point){
    for(auto& x:rooms)
        for(auto& room:x)
            if( room->isPointInRoom( point ) )
                return room;
    return nullptr;
}
