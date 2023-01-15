// Created by tomasz on 16.05.19.

#pragma once

#include "Window.hpp"
#include "Actor.hpp"
#include "AnimatedSprite.hpp"
#include <SFML/Graphics.hpp>
#include "Control.hpp"


template <typename ParentType>
class Drawable : public ParentType, public tt::LocalActor{
protected:
    std::unique_ptr<Observer> onDraw;
    int layer;

public:
    template <typename...Args>
    explicit Drawable(int layer, Args&& ...args):
        ParentType( std::forward<Args>( args )... ),
        onDraw(
            std::make_unique<Observer>
                (
                    scene.base.getActor<Window>().onDraw(
                        layer,
                        [this](sf::RenderTarget& target){
                            target.draw( *this );
                        }
                    )
                )
        ),
        layer( layer ){}

    int getLayer(){
        return layer;
    }

    void setLayer(int layer){
        this->layer = layer;
        onDraw.reset(
            new Observer(
                scene.base.getActor<Window>().onDraw(
                    layer,
                    [this](sf::RenderTarget& target){
                        target.draw( *this );
                    }
                )
            )
        );
    }
};


class AAnimatedSprite : public Drawable<AnimatedSprite>{
private:
    std::unique_ptr<Observer> everyFrame;
    unsigned interval;

public:
    template <typename...Args>
    explicit AAnimatedSprite(Args&& ...args):
        Drawable<AnimatedSprite>( std::forward<Args>( args )... ),
        everyFrame(
            std::make_unique<Observer>(
                scene.onEveryXFrames(
                    1,
                    [this](){ update( sf::seconds( 100 ) ); }
                )
            )
        ),
        interval( 1 ){}

    void setInterval(unsigned interval){
        this->interval = interval;
        everyFrame.reset( new Observer( scene.onEveryXFrames( interval, [this](){ update( sf::seconds( 100 ) ); } ) ) );
    }

    unsigned getInterval(){
        return interval;
    }

    ACTOR_CONTROL_SF( Position, Rotation, Scale, Origin, Interval )

    bool isDrawable() override {
        return true;
    }
};


#define CONTROLLABLE_DRAWABLE_ACTOR_TYPE(NAME, PARENT_NAME, ...) \
class NAME : public Drawable<PARENT_NAME>{ \
public: \
    template <typename...Args> \
    explicit NAME(Args&& ...args): \
        Drawable<PARENT_NAME>( std::forward<Args>( args )... ){} \
    ACTOR_CONTROL_SF( __VA_ARGS__ ) \
    bool isDrawable() override { \
        return true; \
    } \
};


// @formatter:off
CONTROLLABLE_DRAWABLE_ACTOR_TYPE( Sprite, sf::Sprite, Layer,
    Position, Rotation, Scale, Origin, Color )

CONTROLLABLE_DRAWABLE_ACTOR_TYPE( Text, sf::Text, Layer,
    Position, Rotation, Scale, Origin, String, CharacterSize, LineSpacing, LetterSpacing, FillColor )

CONTROLLABLE_DRAWABLE_ACTOR_TYPE( RectangleShape, sf::RectangleShape, Layer,
    Position, Rotation, Scale, Origin, Size, FillColor )

CONTROLLABLE_DRAWABLE_ACTOR_TYPE( CircleShape, sf::CircleShape, Layer,
    Position, Rotation, Scale, Origin, Radius, FillColor )

CONTROLLABLE_DRAWABLE_ACTOR_TYPE( ConvexShape, sf::ConvexShape, Layer,
    Position, Rotation, Scale, Origin, FillColor )

CONTROLLABLE_DRAWABLE_ACTOR_TYPE( Shape, sf::Shape, Layer,
    Position, Rotation, Scale, Origin, FillColor )
// @formatter:on
