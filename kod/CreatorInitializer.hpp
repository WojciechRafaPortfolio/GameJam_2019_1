// Created by tomasz on 23.05.19.

#pragma once

#include <cassert>
#include <vector>

namespace tt{
template <typename ThisType>
class CreatorInitializer{
private:
    static std::vector<ThisType*> creators;

protected:
    void pushCreator(){
        creators.push_back( static_cast<ThisType*>(this) );
    }

    void popCreator(){
        creators.pop_back();
    }

    CreatorInitializer(){
        static_assert( std::is_base_of_v<CreatorInitializer<ThisType>, ThisType> );
    }

public:
    static auto& getCreator(){
        assert( creators.back() );
        assert( !creators.empty() );
        return *creators.back();
    }
};

template <typename ThisType>
std::vector<ThisType*> CreatorInitializer<ThisType>::creators;
}
