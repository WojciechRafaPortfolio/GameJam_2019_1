// Created by tomasz on 04.06.19.

#pragma once

#include "Actor.hpp"
#include "WindowEvents.hpp"


class GlobalWindowEvents : public tt::GlobalActor{
private:
    WindowEvents* currentEvents;

public:
    WindowEvents* getCurrentEvents() const{
        return currentEvents;
    }

    GlobalWindowEvents():
        currentEvents( &getGlogalScene().getBase().getActiveScene().getActor<WindowEvents>() ){}

    void call(const sf::Event& event){
        if( currentEvents )
            currentEvents->call( event );
    }

    void setCurrentEvents(WindowEvents& events){
        currentEvents = &events;
    }

    ACTOR_CONTROL( currentEvents )
};


