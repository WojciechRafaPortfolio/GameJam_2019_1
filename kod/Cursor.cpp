
//
// Created by Wojtek on 07.06.2019.
//
#include "Cursor.hpp"
#include "Room.hpp"
#include "Building.hpp"
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
//#include "Building.hpp"




//#include "GlobalScene.hpp"
//


Cursor::Cursor():
ilosc_obiegow_max(150),
plomyk(scene.createActor<AAnimatedSprite>(20))
{
    sf::Vector2f orgin_plomyk;
    orgin_plomyk.y = plomyk->getAnimation()->getFrame(1).height;
    orgin_plomyk.x = plomyk->getAnimation()->getFrame(1).width;
    plomyk->setOrigin(orgin_plomyk);
}
void Cursor::up_date()
{
    static int powturzenia;// ile razy powtórzył przejście kodu
    static Room* pokuj_ptr = nullptr ;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        auto mousePosition = sf::Mouse::getPosition(scene.getActor<Window>());
        if( pokuj_ptr == scene.getActor<Building >( ).getRoomByPosition(sf::Vector2f(mousePosition.x, mousePosition.y)) )
        {
            powturzenia ++ ;
            if(powturzenia >= ilosc_obiegow_max )
            {
                if(pokuj_ptr != nullptr )
                {
                    //zmień animacje
                    //plomyk->setAnimation();
                    //Rozpal ogień
                    pokuj_ptr->start_fire();
                }

            }
        }else
        {
            powturzenia = 0;
        }
        pokuj_ptr = scene.getActor<Building >( ).getRoomByPosition(sf::Vector2f(mousePosition.x, mousePosition.y));
    }else
    {
        powturzenia = 0 ;
    }

    sf::Vector2f pozycja(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y);
    plomyk->setPosition(pozycja);
}
