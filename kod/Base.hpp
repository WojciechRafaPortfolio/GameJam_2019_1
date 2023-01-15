// Created by tomasz on 23.05.19.

#pragma once

#include <vector>
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "CreatorInitializer.hpp"
#include "GlobalScene.hpp"
#include "OnEveryXCalls.hpp"

namespace tt{
class Scene;

class Base : public CreatorInitializer<Base>, public GlobalScene{
private:
    std::vector<std::unique_ptr<Scene>> scenes;
    bool stopped;
    Scene* activeScene;

private:
    sf::Clock frameClock;
    sf::Time frameTime;

    sf::RenderWindow controlWindow;
    sf::Clock deltaClock;
public:
    Base& getBase() override;
    bool controlDrawables;
private:
    void control();

public:
    void setActiveScene(Scene& scene);
    Scene& getActiveScene() const;
    void stop();
    void run();
    void setFramerate(sf::Int32 framesPerSec);
    sf::Int32 getFramerate();

    static Base& getCreator(){
        return CreatorInitializer<Base>::getCreator();
    }

    template <typename SceneType, typename...Args>
    SceneType& createScene(Args&& ...args){
        CreatorInitializer<Base>::pushCreator();
        auto* newScene = new SceneType( std::forward<Args>( args )... );
        CreatorInitializer<Base>::popCreator();
        scenes.push_back( std::unique_ptr<SceneType>( newScene ) );
        return *newScene;
    }

    Base();
    ~Base();
};
}

