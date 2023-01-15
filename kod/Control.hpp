// Created by tomasz on 02.06.19.

#pragma once

#include <string>
#include <sstream>
#include "Macros.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui_stdlib.h"
#include "Actor.hpp"
#include "ActorPtr.hpp"

#define CALL_CONTROL_WITH_NAME(x) control(#x, x)

#define CALL_CONTROL_WITH_NAME_SF(x) \
auto x = get##x (); \
if( CALL_CONTROL_WITH_NAME(x) ) \
    set##x (x);

#define FUNCTION_GET_TYPE_NAME \
const std::string& getTypeName() override{ \
    static std::string name = __CLASS_NAME__; \
    return name; \
}

#define FUNCTION_CONTROL(...) \
bool controlActor() override{ \
    CALL_MACRO_X_FOR_EACH( CALL_CONTROL_WITH_NAME, __VA_ARGS__ ); \
}

#define FUNCTION_CONTROL_SF(...) \
bool controlActor() override{ \
    CALL_MACRO_X_FOR_EACH( CALL_CONTROL_WITH_NAME_SF, __VA_ARGS__ ); \
}

#define ACTOR_CONTROL(...) \
FUNCTION_CONTROL(__VA_ARGS__) \
FUNCTION_GET_TYPE_NAME

#define ACTOR_NO_CONTROL \
bool controlActor() override{} \
FUNCTION_GET_TYPE_NAME

#define ACTOR_CONTROL_SF(...) \
FUNCTION_CONTROL_SF(__VA_ARGS__) \
FUNCTION_GET_TYPE_NAME

inline auto addressToString(void* v){
    std::ostringstream ss;
    ss << v;
    return ss.str();
}

template <typename T, typename F>
bool defaultControl(const std::string& name, T& v, const std::string& typeName, F function){
    ImGui::Text( "%s", name.c_str() );
    ImGui::NextColumn();
    auto out = function( ("##" + name).c_str(), &v );
    ImGui::NextColumn();
    ImGui::Text( "%s", typeName.c_str() );
    ImGui::NextColumn();
    ImGui::Text( "%s", addressToString( &v ).c_str() );
    ImGui::NextColumn();
    return out;
}

inline bool control(const std::string& name, int& v){
    return defaultControl( name, v, "int", [](auto x, auto y){ return ImGui::DragInt( x, y ); } );
}

inline bool control(const std::string& name, unsigned& v){
    int i = v;
    if( defaultControl( name, i, "unsigned", [](auto x, auto y){ return ImGui::DragInt( x, y ); } ) ){
        v = i;
        return true;
    }
    return false;
}

inline bool control(const std::string& name, float& v){
    return defaultControl( name, v, "float", [](auto x, auto y){ return ImGui::DragFloat( x, y ); } );
}

inline bool control(const std::string& name, bool& v){
    return defaultControl( name, v, "bool", [](auto x, auto y){ return ImGui::Checkbox( x, y ); } );
}

inline bool control(const std::string& name, std::string& v){
    return defaultControl( name, v, "string", [](auto x, auto y){ return ImGui::InputText( x, y ); } );
}

inline bool control(const std::string& name, sf::String& v){
    std::string str = v;
    if( defaultControl( name, str, "string", [](auto x, auto y){ return ImGui::InputText( x, y ); } ) ){
        v = str;
        return true;
    }
    return false;
}

inline bool control(const std::string& name, tt::Actor& v){
    ImGui::PushID( name.c_str() );
    bool changed = defaultControl(
        name, v, v.getTypeName(), [](auto x, auto y){
            if( ImGui::Button( y->isOpened() ? "[less]" : "[more]" ) )
                y->switchOpened();

            if( auto vv = dynamic_cast<tt::LocalActor*>(y); vv ){
                ImGui::SameLine();
                if( ImGui::Button( ("DELETE##" + std::to_string( reinterpret_cast<intptr_t>(vv) )).c_str() ) )
                    vv->destroy();
            }
            return y->isOpened();
        }
    );
    if( changed ){
        if( v.isOpened() ){
            ImGui::Indent();
            v.controlActor();
            ImGui::Unindent();
        }
    }
    ImGui::PopID();
    return changed;
}

inline bool control(const std::string& name, sf::Vector2f& v){
    return defaultControl( name, v.x, "Vector2f", [](auto x, auto y){ return ImGui::DragFloat2( x, y ); } );
}

inline bool control(const std::string& name, sf::Vector2i& v){
    return defaultControl( name, v.x, "Vector2f", [](auto x, auto y){ return ImGui::DragInt2( x, y ); } );
}

inline bool control(const std::string& name, sf::Vector2u& v){
    int ints[2];
    ints[0] = v.x;
    ints[1] = v.y;
    if( defaultControl( name, *ints, "Vector2f", [](auto x, auto y){ return ImGui::DragInt2( x, y ); } ) ){
        v.x = ints[0];
        v.y = ints[1];
        return true;
    }
    return false;
}

inline bool control(const std::string& name, const int& v){
    auto c = v;
    return defaultControl( name, c, "const int", [](auto x, auto y){  ImGui::DragInt( x, y ); return false; } );
}

inline bool control(const std::string& name, const unsigned& v){
    int i = v;
    defaultControl( name, i, "const unsigned", [](auto x, auto y){ return ImGui::DragInt( x, y ); } );
    return false;
}

inline bool control(const std::string& name, const float& v){
    auto c = v;
    return defaultControl( name, c, "const float", [](auto x, auto y){  ImGui::DragFloat( x, y ); return false;  } );
}

inline bool control(const std::string& name, const bool& v){
    auto c = v;
    return defaultControl( name, c, "const bool", [](auto x, auto y){  ImGui::Checkbox( x, y ); return false; } );
}

inline bool control(const std::string& name, const std::string& v){
    auto c = v;
    return defaultControl( name, c, "const string", [](auto x, auto y){  ImGui::InputText( x, y ); return false; } );
}

inline bool control(const std::string& name, const sf::String& v){
    std::string str = v;
    defaultControl( name, str, "const string", [](auto x, auto y){ return ImGui::InputText( x, y ); } );
    return false;
}

inline bool control(const std::string& name, const sf::Vector2f& v){
    auto c = v.x;
    return defaultControl( name, c, "const Vector2f", [](auto x, auto y){ ImGui::DragFloat2( x, y ); return false;  } );
}

inline bool control(const std::string& name, const sf::Vector2i& v){
    auto c = v.x;
    return defaultControl( name, c, "const Vector2f", [](auto x, auto y){ ImGui::DragInt2( x, y ); return false; } );
}

inline bool control(const std::string& name, const sf::Vector2u& v){
    int ints[2];
    ints[0] = v.x;
    ints[1] = v.y;
    defaultControl( name, *ints, "const Vector2f", [](auto x, auto y){ return ImGui::DragInt2( x, y ); } );
    return false;
}

inline bool control(const std::string& name, sf::Color& v){
    ImVec4 imcolor( v.r / 255.f, v.g / 255.f, v.b / 255.f, v.a / 255.f );
    if( defaultControl( name, imcolor.x, "Color", [](auto x, auto y){ return ImGui::ColorEdit4( x, y ); } ) ){
        v.r = static_cast<sf::Uint8>(imcolor.x * 255.f);
        v.g = static_cast<sf::Uint8>(imcolor.y * 255.f);
        v.b = static_cast<sf::Uint8>(imcolor.z * 255.f);
        v.a = static_cast<sf::Uint8>(imcolor.w * 255.f);
        return true;
    }
    return false;
}

template <typename T>
bool control(const std::string& name, const T*&& v){
    defaultControl(
        name, v, "pointer", [](auto x, auto y){
            std::stringstream ss;
            ss << &y;
            ImGui::Text( ss.str().c_str() );
            return false;
        }
    );
    return false;
}

template <typename T>
bool control(const std::string& name, ActorPtr<T>& v){
    defaultControl(
        name, *v.get(), "ActorPtr<" + v->getTypeName() + '>', [](auto x, auto y){
            ImGui::Text( x, y );
            return false;
        }
    );
    return false;
}
