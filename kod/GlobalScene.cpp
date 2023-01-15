// Created by tomasz on 28.05.19.

#include "imgui-SFML.h"
#include "imgui.h"
#include "Base.hpp"
#include <SFML/Window/Event.hpp>
#include "Control.hpp"
#include "Actor.hpp"
#include "Scene.hpp"
#include "GlobalScene.hpp"

void tt::GlobalScene::controlGlobals(){
    for(auto& i: allActorsVectors)
        i->control(id);
}

Observer tt::GlobalScene::onEveryXFrames(uint64_t x, decltype(callerEveryXFrames)::FuncRefType func){
    return callerEveryXFrames.createObserver( func, x );
}

namespace tt{
decltype( GlobalScene::topId ) GlobalScene::topId;
}
