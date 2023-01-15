// Created by tomasz on 28.05.19.

#include "FontBank.hpp"
#include "Game.hpp"

sf::Font& FontBank::getFont(const sf::String& name){
    auto found = fonts.find( name );
    if( found == fonts.end() ){
        found = fonts.insert( {name, std::make_unique<sf::Font>()} ).first;
        if( !found->second->loadFromFile( name ) )
            warning( "Cannot load font from file \"" + name + "\"." );
    }
    return *found->second;
}
