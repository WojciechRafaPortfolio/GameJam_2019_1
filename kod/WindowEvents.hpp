#pragma once

#include <SFML/Window/Event.hpp>
#include "Caller.hpp"
#include "Actor.hpp"
#include "Control.hpp"
#include "ListenerDraw.hpp"

#define CALLER_ONE_ARG(NAME,ARGTYPE)                         \
private:                                                     \
Caller< const sf::Event::ARGTYPE##Event& > caller##NAME;     \
public:                                                      \
Observer on##NAME(decltype(caller##NAME)::FuncRefType func){ \
    return caller##NAME.createObserver( func );              \
}

#define CALLER_NO_ARG(NAME)                                  \
private:                                                     \
Caller<> caller##NAME;                                       \
public:                                                      \
Observer on##NAME(decltype(caller##NAME)::FuncRefType func){ \
    return caller##NAME.createObserver( func );              \
}

class WindowEvents : public tt::GlobalActor{
private:
    Observer sceneFocusObserver;
public:

    CallerDraw<sf::RenderTarget&> drawablesCaller;
    WindowEvents();

    // Observer onEVENT(func);
    CALLER_NO_ARG( Closed )
    CALLER_ONE_ARG( Resized, Size )
    CALLER_NO_ARG( LostFocus )
    CALLER_NO_ARG( GainedFocus )
    CALLER_ONE_ARG( TextEntered, Text )
    CALLER_ONE_ARG( KeyPressed, Key )
    CALLER_ONE_ARG( KeyReleased, Key )
    CALLER_ONE_ARG( MouseWheelMoved, MouseWheel )
    CALLER_ONE_ARG( MouseWheelScrolled, MouseWheelScroll )
    CALLER_ONE_ARG( MouseButtonPressed, MouseButton )
    CALLER_ONE_ARG( MouseButtonReleased, MouseButton )
    CALLER_ONE_ARG( MouseMoved, MouseMove )
    CALLER_NO_ARG( MouseEntered )
    CALLER_NO_ARG( MouseLeft )
    CALLER_ONE_ARG( JoystickButtonPressed, JoystickButton )
    CALLER_ONE_ARG( JoystickButtonReleased, JoystickButton )
    CALLER_ONE_ARG( JoystickMoved, JoystickMove )
    CALLER_ONE_ARG( JoystickConnected, JoystickConnect )
    CALLER_ONE_ARG( JoystickDisconnected, JoystickConnect )
    CALLER_ONE_ARG( TouchBegan, Touch )
    CALLER_ONE_ARG( TouchMoved, Touch )
    CALLER_ONE_ARG( TouchEnded, Touch )
    CALLER_ONE_ARG( SensorChanged, Sensor )

public:
    void call(const sf::Event&);

    bool controlActor() override{};
    FUNCTION_GET_TYPE_NAME
};
