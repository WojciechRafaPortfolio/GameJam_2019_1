// Created by tomasz on 04.05.19.

#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "WindowEvents.hpp"
#include "Actor.hpp"
#include "Config.hpp"
#include "Scene.hpp"
#include "Control.hpp"
#include "GlobalWindowEvents.hpp"


class Window : public tt::GlobalActor, public sf::RenderWindow{
private:
    Config config;
    Observer everyFrame;

public:
    Window():
        tt::GlobalActor( "main window" ),
        config( getGlogalScene().config.get( "Window" ) ),
        everyFrame(
            getGlogalScene().onEveryStep(
                [this](){
                    sf::Event event{};
                    while( pollEvent( event ) ){
                        getGlogalScene().getActor<GlobalWindowEvents>().call( event );
                        if( event.type == sf::Event::Closed )
                            close();
                    }

                    clear();
                    getGlogalScene().getActor<GlobalWindowEvents>().getCurrentEvents()->drawablesCaller.call( *this );
                    display();
                }
            )
        ){
        sf::RenderWindow::create(
            sf::VideoMode( config.get<int>( "size.x" ), config.get<int>( "size.y" ) ),
            config.get<std::string>( "name" )
        );
    };


    auto onDraw(int layer, decltype(WindowEvents::drawablesCaller)::FuncRefType func){
        return getGlogalScene().getActor<GlobalWindowEvents>().getCurrentEvents()->drawablesCaller.createObserver( func, layer );
    }
    ACTOR_CONTROL_SF(Size, Position)

    // bool controlActor() override{}
    //
    // FUNCTION_GET_TYPE_NAME
};


