// Created by tomasz on 07.06.19.

#include "Human.hpp"
#include "Layers.hpp"
#include "AnimationBank.hpp"
#include "AConfig.hpp"

Human::Human():
    sprite( scene.createActor<AAnimatedSprite>( e_human ) ){
    sprite->setAnimation(
        scene.base
             .getActor<AnimationBank>()
             .getAnimation( scene.base.getActor<AConfig>().get<std::string>( "Animations", "humanAnimation" ) )
    );
}
