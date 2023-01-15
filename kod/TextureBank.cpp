// Created by tomasz on 28.05.19.

#include "TextureBank.hpp"
#include "Game.hpp"

sf::Texture& TextureBank::getTexture(const sf::String& name){
    auto found = textures.find( name );
    if( found == textures.end() ){
        found = textures.insert( {name, std::make_unique<sf::Texture>()} ).first;
        if( !found->second->loadFromFile( name ) )
            if( !found->second->loadFromFile( name + ".png" ) )
                if( !found->second->loadFromFile( name + ".jpg" ) )
                    warning( "Cannot load texture from file \"" + name + "\"." );
    }
    return *found->second;
}
