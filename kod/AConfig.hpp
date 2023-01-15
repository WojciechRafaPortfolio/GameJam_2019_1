// Created by tomasz on 07.06.19.

#pragma once

#include "Actor.hpp"
#include "Config.hpp"
#include "Control.hpp"


class AConfig : public tt::GlobalActor{
private:
    Config defaultConfig;

public:
    AConfig():
        defaultConfig( "config" ){}

    template <typename T = Config>
    inline T get(const std::string& name){
        return defaultConfig.get<T>( name );
    }

    inline Config getConfig(const std::string& fileName){
        Config config( fileName );
        return config;
    }

    template <typename T = Config>
    inline T get(const std::string& fileName, const std::string& name){
        Config config( fileName );
        return config.get<T>( name );
    }

    ACTOR_NO_CONTROL
};


