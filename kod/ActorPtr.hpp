// Created by tomasz on 04.06.19.

#pragma once

#include "Actor.hpp"
#include <memory>

template <typename T>
class ActorPtr{
private:
    T* ptr;

public:
    explicit ActorPtr(T& t):
        ptr( &t ){
        static_assert( std::is_base_of_v<tt::Actor, T> );
    }

    explicit ActorPtr(nullptr_t):
        ptr( nullptr ){
        static_assert( std::is_base_of_v<tt::Actor, T> );
    }

    ActorPtr(ActorPtr&& other):
        ptr( other.ptr ){
        other.ptr = nullptr;
    };

    ActorPtr& operator=(ActorPtr&& other){
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    ActorPtr(ActorPtr&) = delete;
    ActorPtr& operator=(ActorPtr&) = delete;

    T* operator->(){
        return ptr;
    }

    T* operator*(){
        return ptr;
    }

    operator T*(){
        return ptr;
    }

    T* get(){
        return ptr;
    }

    void reset(T& t){
        static_assert( std::is_base_of_v<tt::Actor, std::remove_reference<T>> );
        if( ptr )
            ptr->destroy();
        ptr = &t;
    }

    void reset(nullptr_t){
        static_assert( std::is_base_of_v<tt::Actor, std::remove_reference<T>> );
        if( ptr )
            ptr->destroy();
        ptr = nullptr;
    }

    ~ActorPtr(){
        if( ptr )
            ptr->destroy();
    }
};
