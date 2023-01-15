// Created by tomasz on 4/17/19.

#include "GameConfig.hpp"

std::unique_ptr<b2Shape> GameConfig::getShape(const std::string& name){
    auto shapeConf = get( name );
    auto type = shapeConf.get<std::string>( "type" );
    if( type == "polygon" ){
        auto count = shapeConf.get<int>( "count" );
        auto verticles = std::make_unique<b2Vec2[]>( count );
        for(int i = 0; i < count; ++i){
            Config verticleConf = shapeConf.get( std::to_string( i ) );
            verticles[i].Set( verticleConf.get<float>( "x" ), verticleConf.get<float>( "y" ) );
        }
        auto shape = std::make_unique<b2PolygonShape>();
        shape->Set( verticles.get(), count );
        return shape;
    }else if( type == "circle" ){
        auto radius = shapeConf.get<float>( "radius" );
        auto shape = std::make_unique<b2CircleShape>();
        shape->m_radius = radius;
        return shape;
    }else{
        warning( "Invalid shape type in " + name );
        return nullptr;
    }
}

std::unique_ptr<b2FixtureDef> GameConfig::getFixtureDef(const std::string& name){
    auto def = std::make_unique<b2FixtureDef>();
    def->shape = getShape( name + ".shape" ).release();
    def->friction = get<float>( name + ".friction" );
    def->restitution = get<float>( name + ".restitution" );
    def->density = get<float>( name + ".density" );
    def->isSensor = get<bool>( name + ".isSensor" );
    return def;
}

std::unique_ptr<b2BodyDef> GameConfig::getBodyDef(const std::string& name){
    auto defConf = get( name );
    auto def = std::make_unique<b2BodyDef>();
    def->position.Set( defConf.get<float>( "position.x" ), defConf.get<float>( "position.y" ) );
    def->angle = defConf.get<float>( "angle" );
    def->linearVelocity.Set( defConf.get<float>( "linearVelocity.x" ), defConf.get<float>( "linearVelocity.y" ) );
    def->angularVelocity = defConf.get<float>( "angularVelocity" );
    def->linearDamping = defConf.get<float>( "linearDamping" );
    def->angularDamping = defConf.get<float>( "angularDamping" );
    def->allowSleep = defConf.get<bool>( "allowSleep" );
    def->awake = defConf.get<bool>( "awake" );
    def->fixedRotation = defConf.get<bool>( "fixedRotation" );
    def->bullet = defConf.get<bool>( "bullet" );
    def->active = defConf.get<bool>( "active" );
    def->gravityScale = defConf.get<float>( "gravityScale" );

    auto type = defConf.get<std::string>( "type" );
    if( type == "static" )
        def->type = b2_staticBody;
    else if( type == "kinematic" )
        def->type = b2_kinematicBody;
    else if( type == "dynamic" )
        def->type = b2_dynamicBody;
    else
        warning( "Invalid body type in " + name );
    return def;
}

GameConfig::GameConfig(const std::string& filename):
    Config( filename ){}
