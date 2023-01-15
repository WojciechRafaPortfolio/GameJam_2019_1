// Created by tomasz on 07.06.19.

#pragma once

#include "Actor.hpp"
#include "Caller.hpp"
#include "Control.hpp"
#include "Drawable.hpp"
#include "Human.hpp"


class RoomCommon : public tt::GlobalActor{
public:
    float fireSpeed;
    float smokeSpeed;
    float fireDumping;
    float startFire;
    float fireKilling;
    RoomCommon();

    ACTOR_CONTROL( fireSpeed, smokeSpeed, fireDumping, startFire, fireKilling )
};


class Room : public tt::LocalActor{
private:
    const int x, y;

    bool window;

    float fire;

    ///dym
    float smoke;

    ActorPtr<Sprite> sInside;
    ActorPtr<Sprite> sGlass;
    ActorPtr<Sprite> sWall;
    ActorPtr<AAnimatedSprite> sFire;
    ActorPtr<AAnimatedSprite> sSmoke;

    std::vector<ActorPtr<Human>> humans;

    Observer doEveryFrame;

public:
    Room(int x, int y, const sf::Vector2f& position);
    sf::Vector2f getSize();
    float getFire() const;
    float getSmoke() const;
    void makeSmoke(float smoke);

    bool isPointInWindow(const sf::Vector2f&);
    void breakWindow();
    void killFire();
    void saveHuman();
    bool ifIsSomeone();
    void start_fire();
    bool isPointInRoom(sf::Vector2f);

    ACTOR_CONTROL( window, fire, smoke, x, y )
};


