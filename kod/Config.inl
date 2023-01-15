#include "Game.hpp"
#include <functional>

template <typename T>
std::map<std::string, T> Config::data;

template <typename T>
void Config::addValue(const std::string& name, T&& value){
    data<std::remove_reference_t<decltype( value )>>.insert( std::pair{_scope + name, value} );
}

template <typename T>
T&& Config::get(const std::string& name){
    auto found = data<T>.find( _scope + name );
    if( found == data<T>.end() ){
        auto type = getType(typeid(T).hash_code());
        if(type == nullptr)
            fatalError( "Tried to load unsupported type." );
        const auto messageBegin = "Value \"" + _scope + name + "\" of type " + type->name + " not found.\n";
        if constexpr( std::is_constructible_v<T> ){
            warning( messageBegin + "Initializing with default value." );
            return std::move( T() );
        }else{
            fatalError( messageBegin );
        }
    }
    return std::move( found->second );
}

