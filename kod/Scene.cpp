// Created by tomasz on 19.05.19.

#include "Scene.hpp"
#include "Actor.hpp"
#include "GlobalScene.hpp"

namespace tt{
unsigned Scene::topSceneId = 0;

void Scene::destroyActor(LocalActor& actor){
    auto iter = std::find_if(
        actors.begin(),
        actors.end(),
        [&actor](auto& i){ return i.get() == &actor; }
    );
    iter->reset();
}

void Scene::beforeAdding(){
    CreatorInitializer<Scene>::pushCreator();
}

void Scene::afterAdding(){
    CreatorInitializer<Scene>::popCreator();
}

GlobalScene& Scene::otherStorageThatMayHaveThisActor(){
    return *this;// return base;
}

void Scene::controlLocals(){
    for(auto& i: actors){
        if(i){
            if(!(!base.controlDrawables && i->isDrawable())){
                ::control( i->getName(), *i );
                ImGui::Separator();
            }
        }
    }
}

Base& Scene::getBase(){
    return base;
}
}
