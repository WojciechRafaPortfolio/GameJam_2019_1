// Created by tomasz on 04.05.19.

#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include "Config.hpp"
#include "Caller.hpp"
#include "CreatorInitializer.hpp"
#include "Base.hpp"
#include "Actor.hpp"
#include "GlobalScene.hpp"

namespace tt{

class Scene : public CreatorInitializer<Scene>, public GlobalScene{
private:
    static unsigned topSceneId;
    const unsigned sceneId;
    const std::string name;

    std::vector<std::unique_ptr<LocalActor>> actors;

    void beforeAdding() override;
    void afterAdding() override;
    GlobalScene& otherStorageThatMayHaveThisActor() override;

    Caller<> getFocus;

public:

    void gotFocus(){
        getFocus.call();
    }

    Base& base;

    explicit Scene(const std::string& name):
        GlobalScene( name ),
        sceneId( ++topSceneId ),
        name( name + std::to_string( sceneId ) ),
        base( Base::getCreator() ){}

    Scene(Scene&) = delete;
    Scene& operator=(const Scene&) = delete;

    ~Scene(){
        while( !actors.empty() )
            actors.pop_back();
    }

    static Scene& getCreator(){
        return CreatorInitializer<Scene>::getCreator();
    }

    void step(){
        callerEveryStep.call();
        callerEveryXFrames.call();
        for(auto i = actors.begin(); i != actors.end(); i++){
            if( i->get() == nullptr ){
                actors.erase( i );
                if(actors.empty())
                    break;
                i = actors.begin();
            }
        }
    }

    auto onFocus(decltype(getFocus)::FuncRefType func){
        return getFocus.createObserver( func );
    }

    template <typename ActorType, typename ...Args>
    ActorType& createActor(Args&& ...args){
        CreatorInitializer<Scene>::pushCreator();
        auto* newActor = new ActorType( std::forward<Args>( args )... );
        CreatorInitializer<Scene>::popCreator();
        actors.push_back( std::unique_ptr<LocalActor>( newActor ) );
        return *newActor;
    }

    void destroyActor(LocalActor& actor);

    const std::vector<std::unique_ptr<LocalActor>>& getActors() const{
        return actors;
    }

    void controlLocals();
    Base& getBase() override;

    const std::string& getMyName(){
        return name;
    }
};
}
