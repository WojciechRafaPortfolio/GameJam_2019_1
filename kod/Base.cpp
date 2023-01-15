// Created by tomasz on 23.05.19.

#include <SFML/Window/Event.hpp>
#include "Base.hpp"
#include "Scene.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "GlobalScene.hpp"

namespace tt{

Base::Base():
    GlobalScene( "Base" ),
    stopped( false ),
    activeScene( nullptr ),
    controlDrawables( true ),
    controlWindow( {640, 480}, "Control", sf::Style::Resize ){
    ImGui::SFML::Init( controlWindow );
}

Base::~Base(){
    ImGui::SFML::Shutdown();
}

void Base::setActiveScene(Scene& scene){
    // assert(
    //     std::find_if( scenes.begin(), scenes.end(), [&scene](auto& i){ return i.get() == &scene; } ) != scenes.end()
    // );
    activeScene = &scene;
    activeScene->gotFocus();
}

void Base::stop(){
    stopped = true;
}

void Base::run(){
    while( !stopped ){
        control();
        callerEveryXFrames.call();
        // callerAfterXFrames.call();
        callerEveryStep.call();
        frameClock.restart();
        assert( activeScene );
        activeScene->step();
        if( frameTime != sf::Time::Zero )
            if( frameClock.getElapsedTime() < frameTime )
                sf::sleep( frameTime - frameClock.getElapsedTime() );
    }
}

void Base::setFramerate(sf::Int32 framesPerSec){
    frameTime = sf::milliseconds( 1000 / framesPerSec );
}

sf::Int32 Base::getFramerate(){
    return frameTime.asMilliseconds();
}

void Base::control(){
    sf::Event event{};
    while( controlWindow.pollEvent( event ) )
        ImGui::SFML::ProcessEvent( event );

    ImGui::SFML::Update( controlWindow, deltaClock.restart() );
    ImGui::SetNextWindowPos( {0, 0} );
    ImGui::SetNextWindowSize( controlWindow.getSize() );
    ImGui::Begin(
        "Hello, world!",
        nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
    );
    ImGui::Columns( 1 );
    if( ImGui::BeginTabBar( "tab bar" ) ){
        if( ImGui::BeginTabItem( "BASE" ) ){
            ImGui::Columns( 4 );
            ::CALL_CONTROL_WITH_NAME( controlDrawables );
            controlGlobals();
            ImGui::EndTabItem();
        }
        for(auto& i: scenes){
            auto displayName = i->getMyName();
            if( i.get() == activeScene ){
                displayName.push_back( ']' );
                displayName.insert( 0, "[" );
            }
            ImGui::Columns( 1 );
            if( ImGui::BeginTabItem( (displayName + "###" + i->getMyName()).c_str() ) ){
                ImGui::Separator();
                ImGui::Text( "GLOBALS" );
                ImGui::Separator();
                ImGui::Columns( 4 );
                i->controlGlobals();
                ImGui::Separator();
                ImGui::Columns( 1 );
                ImGui::Text( "LOCALS" );
                ImGui::Separator();
                ImGui::Columns( 4 );
                i->controlLocals();
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
    ImGui::End();
    controlWindow.clear();
    ImGui::SFML::Render( controlWindow );
    controlWindow.display();
}

Scene& Base::getActiveScene() const{
    return *activeScene;
}

Base& Base::getBase(){
    return *this;
}
}
