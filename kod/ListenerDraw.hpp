// Created by tomasz on 05.06.19.

#pragma once

#include "Caller.hpp"


template <typename...Args>
class ListenerDraw : public Listener<Args...>{
public:
    using Parent = Listener<Args...>;
    using CallerType = typename Parent::CallerType;

    int layer;

public:
    ListenerDraw(typename CallerType::FuncRefType func, int layer):
        Parent( func ),
        layer( layer ){}

    bool isOkToEmplaceBefore(Listener<Args...>& listener) const override{
        return layer >= dynamic_cast<ListenerDraw&>(listener).layer;
    }
};


template <typename...Args>
using CallerDraw = CallerTemplate<ListenerDraw < Args...>, Args...>;

