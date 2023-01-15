// Created by tomasz on 07.06.19.

#pragma once

#include "Scene.hpp"
#include "Building.hpp"


class MainGame : public tt::Scene{
private:
    Observer doOnWindowClosed;

public:
    MainGame():
        Scene( "MainGame" ),
        doOnWindowClosed( getActor<WindowEvents>().onClosed( [this](){ base.stop(); } ) ){
        base.setActiveScene( *this );
        getActor<Building>();
    }
};


