// Created by tomasz on 05.06.19.

#include <fstream>
#include "AnimationBank.hpp"
#include "GlobalScene.hpp"
#include "Base.hpp"

#include "Game.hpp"
#include "TextureBank.hpp"

Animation& AnimationBank::getAnimation(const sf::String& name){
    auto found = animations.find( name );
    if( found == animations.end() ){
        found = animations.insert( {name, std::make_unique<Animation>()} ).first;
        if( !loadFromFile( *found->second, name ) )
            warning( "Cannot load animation from file \"" + name + "\"." );
    }
    return *found->second;
}

bool AnimationBank::loadFromFile(Animation& animation, const sf::String& filename){
    std::ifstream file( filename );
    if( !file.good() )
        return false;

    std::string texturePath;
    file >> texturePath;
    animation.setSpriteSheet( getGlogalScene().getBase().getActor<TextureBank>().getTexture( texturePath ) );

    std::string word;
    do{
        if( !file.good() )
            return false;

        sf::IntRect frameRect;
        file >> frameRect.left;
        file >> frameRect.top;
        file >> frameRect.width;
        file >> frameRect.height;
        animation.addFrame( frameRect );

        auto pos = file.tellg();
        file >> word;
        file.seekg( pos );
    }while( word != "end" );

    return file.good();
}
