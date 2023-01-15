// Created by tomasz on 28.05.19.

#pragma once

#include <vector>
#include <memory>
#include <cassert>
#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Config.hpp"
#include "Caller.hpp"
#include "CreatorInitializer.hpp"
#include "Control.hpp"
#include "OnEveryXCalls.hpp"

namespace tt{

class GlobalScene : public CreatorInitializer<GlobalScene>{
    /// Even if we don't know T, we know std::unique_ptr<T> have member reset().
    /// So this is interface for reseting i-th ptr in vector independly from T.
    class VectorWithResetablePtr{
    public:
        /// Resets i-th element of vector.
        virtual void resetPointer(std::size_t) = 0;
        virtual void control(std::size_t id) = 0;
    };

    template <typename ActorType>
    using stdPtrVector = std::vector<std::unique_ptr<ActorType>>;

private:
    /// Just Vector of std::unique_ptr<T>, but we can reset i-th pointer without knowing
    template <typename ActorType>
    class VectorOfActorPtrs : public stdPtrVector<ActorType>, public VectorWithResetablePtr{
    public:
        void resetPointer(std::size_t i) override{
            stdPtrVector<ActorType>::operator[]( i ).reset();
        }

        void control(std::size_t id) override{
            auto& ref = stdPtrVector<ActorType>::operator[]( id );
            ::control( ref->getName(), *ref );
        }
    };

    /// Actors for all Scenes as stored here.
    /// (Workaround: non-static template fields are not allowed).
    /// Actor in allActors[i] belongs to scene with id==i. id needs to be unique.
    template <typename ActorType>
    static VectorOfActorPtrs<ActorType> allActors;

    /// Pointers to vectors in allActors.
    std::vector<VectorWithResetablePtr*> allActorsVectors;

private:

    /// Helps to making unique id.
    static std::size_t topId;

    /// Which actor belongs to this scene? allActors[id]
    const std::size_t id;

    std::string name;

private:

    virtual void beforeAdding(){};

    virtual void afterAdding(){};

    virtual GlobalScene& otherStorageThatMayHaveThisActor(){
        return *this;
    }

    template <typename ActorType>
    ActorType& getActorImplementation(){
        static_assert(
            std::is_constructible_v<ActorType>,
            "All global actors needs to be created by default constructor. "
            "If you need to do some initialization, use Config class."
        );

        // This if is true only once for every allActors vector.
        // It's needed to know where are used allActors vectors
        // to find all actors used by Scene.
        // This is used in destructor.
        //if( allActors<ActorType>.size() == 0 )
        if( std::find( allActorsVectors.begin(), allActorsVectors.end(), &allActors<ActorType> ) ==
            allActorsVectors.end() )
            allActorsVectors.push_back( &allActors<ActorType> );

        // Fill unused pointers with null. Waste, but not big one.
        while( allActors<ActorType>.size() < id )
            allActors<ActorType>.push_back( nullptr );

        if( allActors<ActorType>.size() == id ){
            beforeAdding();
            pushCreator();
            allActors<ActorType>.push_back( std::make_unique<ActorType>() );
            popCreator();
            afterAdding();
        }else if( allActors<ActorType>[id].get() == nullptr ){
            beforeAdding();
            pushCreator();
            allActors<ActorType>[id] = std::make_unique<ActorType>();
            popCreator();
            afterAdding();
        }
        auto* out = allActors<ActorType>[id].get();
        assert( out );
        return *out;
    }

protected:
    Caller<> callerEveryStep;

    CallerEveryXCalls<> callerEveryXFrames;
public:
    Config config;

    explicit GlobalScene(const std::string& name):
        config( name ),
        name( name ),
        id( topId++ ){}

    virtual ~GlobalScene(){
        // Deletes actors belonging to this scene
        for(auto& actorsVector : allActorsVectors)
            actorsVector->resetPointer( id );
    }

    auto onEveryStep(decltype(callerEveryStep)::FuncRefType func){
        return callerEveryStep.createObserver( func );
    }

    template <typename ActorType>
    bool haveActor(){
        if( allActors<ActorType>.size() <= id )
            return false;
        return allActors<ActorType>[id].get();
    }

    /// Returns pointer to actor of given type from this scene.
    /// If this actor doesn't exist, creates it.
    template <typename ActorType>
    ActorType& getActor(){
        if( !haveActor<ActorType>() ){
            auto& other = otherStorageThatMayHaveThisActor();
            if( other.haveActor<ActorType>() )
                return other.getActorImplementation<ActorType>();
        }
        return getActorImplementation<ActorType>();
    }

    const auto& getAllActorsVectors(){
        return allActorsVectors;
    }

    void controlGlobals();

    const std::string& getName() const{
        return name;
    }

    Observer onEveryXFrames(uint64_t x, decltype(callerEveryXFrames)::FuncRefType func);

    virtual Base& getBase() = 0;
};


template <typename ActorType>
GlobalScene::VectorOfActorPtrs<ActorType> GlobalScene::allActors;
}
