// Created by tomasz on 30.05.19.

#pragma once

#include "Caller.hpp"


template <typename...Args>
class ListenerEveryXCalls : public Listener<Args...>{
public:
    using Parent = Listener<Args...>;
    using CallerType = typename Parent::CallerType;

private:
    unsigned delay;
    unsigned framesToNextCall;

public:
    ListenerEveryXCalls(typename CallerType::FuncRefType func, unsigned delay):
        Parent( func ),
        delay( delay ),
        framesToNextCall( delay ){
    }

    bool isOkToCallNow() override{
        if( --framesToNextCall == 0 ){
            framesToNextCall = delay;
            return true;
        }
        return false;
    }
};

template <typename...Args>
using CallerEveryXCalls = CallerTemplate<ListenerEveryXCalls<Args...>, Args...>;

