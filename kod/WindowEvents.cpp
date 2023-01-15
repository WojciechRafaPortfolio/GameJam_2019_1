#include "WindowEvents.hpp"

#include <cassert>
#include "Scene.hpp"
#include "GlobalWindowEvents.hpp"

void WindowEvents::call(const sf::Event& event){
    switch( event.type ){
    case sf::Event::Closed: callerClosed.call();
        break;
    case sf::Event::Resized: callerResized.call( event.size );
        break;
    case sf::Event::LostFocus: callerLostFocus.call();
        break;
    case sf::Event::GainedFocus: callerGainedFocus.call();
        break;
    case sf::Event::TextEntered: callerTextEntered.call( event.text );
        break;
    case sf::Event::KeyPressed: callerKeyPressed.call( event.key );
        break;
    case sf::Event::KeyReleased: callerKeyReleased.call( event.key );
        break;
    case sf::Event::MouseWheelMoved: callerMouseWheelMoved.call( event.mouseWheel );
        break;
    case sf::Event::MouseWheelScrolled: callerMouseWheelScrolled.call( event.mouseWheelScroll );
        break;
    case sf::Event::MouseButtonPressed: callerMouseButtonPressed.call( event.mouseButton );
        break;
    case sf::Event::MouseButtonReleased: callerMouseButtonReleased.call( event.mouseButton );
        break;
    case sf::Event::MouseMoved: callerMouseMoved.call( event.mouseMove );
        break;
    case sf::Event::MouseEntered: callerMouseEntered.call();
        break;
    case sf::Event::MouseLeft: callerMouseLeft.call();
        break;
    case sf::Event::JoystickButtonPressed: callerJoystickButtonPressed.call( event.joystickButton );
        break;
    case sf::Event::JoystickButtonReleased: callerJoystickButtonReleased.call( event.joystickButton );
        break;
    case sf::Event::JoystickMoved: callerJoystickMoved.call( event.joystickMove );
        break;
    case sf::Event::JoystickConnected: callerJoystickConnected.call( event.joystickConnect );
        break;
    case sf::Event::JoystickDisconnected: callerJoystickDisconnected.call( event.joystickConnect );
        break;
    case sf::Event::TouchBegan: callerTouchBegan.call( event.touch );
        break;
    case sf::Event::TouchMoved: callerTouchMoved.call( event.touch );
        break;
    case sf::Event::TouchEnded: callerTouchEnded.call( event.touch );
        break;
    case sf::Event::SensorChanged: callerSensorChanged.call( event.sensor );
        break;
    default: assert( false && "unknown Event type" );
    }
}

WindowEvents::WindowEvents():
    GlobalActor( "WindowEvents" ),
    sceneFocusObserver(
        dynamic_cast<tt::Scene&>(getGlogalScene()).onFocus(
            [this](){
                getGlogalScene().getBase().getActor<GlobalWindowEvents>().setCurrentEvents( *this );
            }
        )
    ){}
