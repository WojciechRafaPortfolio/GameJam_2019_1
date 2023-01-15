#pragma once

#include <functional>
#include <vector>
#include <memory>
#include <cassert>


class IListener{
public:
    virtual ~IListener() = default;
};


class Observer;


class ICaller{
public:
    virtual ~ICaller() = default;
    virtual void removeListener(Observer* observer) = 0;
    virtual void updateObserverPtr(Observer* oldObserver, Observer* newObserver) = 0;
};


class Observer{
    template <typename ListenerType, typename...Args>
    friend
    class CallerTemplate;

private:
    Observer(ICaller& caller, IListener* listener):
        caller( &caller ){};

    ICaller* caller;

public:
    ~Observer(){
        if( caller ){
            caller->removeListener( this );
            clear();
        }
    }

    Observer& operator=(Observer& other) = delete;
    Observer(Observer& other) = delete;

    Observer& operator=(Observer&& other) noexcept{
        caller = other.caller;
        caller->updateObserverPtr( &other, this );
        other.caller = nullptr;
        return (*this);
    }

    Observer(Observer&& other):
        caller( other.caller ){
        caller->updateObserverPtr( &other, this );
        other.caller = nullptr;
    }

    void reset(Observer&& other){
        operator=( std::forward<Observer&&>( other ) );
    }

    void clear(){
        caller = nullptr;
    }
};


template <typename ListenerType, typename...Args>
class CallerTemplate : public ICaller{
public:
    using FuncType = void(Args&& ...);
    using FuncRefType = std::function<FuncType>;

private:
    struct CallStuff{
        CallStuff(ListenerType* listener, Observer* observer):
            observer( observer ),
            listener( listener ){}

        std::unique_ptr<ListenerType> listener;
        Observer* observer;
    };

    std::vector<CallStuff> calls;
    std::vector<ListenerType*> copy;
    bool needCopy;

public:

    CallerTemplate():
        needCopy( false ){
        static_assert( std::is_base_of_v<IListener, ListenerType> );
    }

    virtual ~CallerTemplate(){
        for(auto& i:calls)
            i.observer->clear();
    }

    template <typename...Inits>
    Observer createObserver(FuncRefType func, Inits&& ...inits){
        auto* listener = new ListenerType( func, std::forward<Inits>( inits )... );
        needCopy = true;
        for(auto i = calls.begin(), end = calls.end(); i != end; ++i){
            if( listener->isOkToEmplaceBefore( *i->listener ) ){
                Observer observer( *this, listener );
                calls.emplace( i, listener, &observer );
                return observer;
            }
        }
        Observer observer( *this, listener );
        calls.emplace_back( listener, &observer );
        return observer;
    }

    void removeListener(Observer* observer) override{
        needCopy = true;
        auto found = std::find_if(
            calls.begin(),
            calls.end(),
            [observer](auto& i){ return i.observer == observer; }
        );
        assert( found != calls.end() && "Attempt to delete non-existing listener" );
        found->observer->clear();
        calls.erase( found );
        assert( std::find_if(
            calls.begin(),
            calls.end(),
            [observer](auto& i){ return i.observer == observer; }
        ) == calls.end() && "Faild to delete listener or pointer to listener was doubled" );
    }

    void updateObserverPtr(Observer* oldObserver, Observer* newObserver) override{
        auto found = std::find_if(
            calls.begin(),
            calls.end(),
            [oldObserver](auto& i){ return i.observer == oldObserver; }
        );
        assert( found != calls.end() );
        found->observer = newObserver;
    }

    void call(Args&& ...args){
        if( needCopy ){
            copy.clear();
            for(auto& i:calls)
                copy.push_back( i.listener.get() );
            needCopy = false;
        }
        for(auto i:copy)
            i->call( std::forward<Args>( args )... );
    }
};


template <typename...Args>
class Listener : public IListener{
public:
    using CallerType = CallerTemplate<Listener, Args...>;

private:
    typename CallerType::FuncRefType func;

public:
    Listener(typename CallerType::FuncRefType& func):
        func( func ){}

    virtual bool isOkToEmplaceBefore(Listener&) const{
        return true;
    }

    virtual bool isOkToCallNow(){
        return true;
    }

    void call(Args&& ...args){
        if( isOkToCallNow() )
            func( std::forward<Args>( args )... );
    };
};


template <typename...Args>
using Caller = CallerTemplate<Listener<Args...>, Args...>;
