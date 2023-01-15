#include "Config.hpp"

#include "Game.hpp"
#include <fstream>
#include <algorithm>

// @formatter:off

const std::vector< Config::ConfigType> Config::types {
    {"int", typeid(int).hash_code(), [](VariableLoadData&& data){
        auto value = loadWord( data.file, "Unexpected EOF instead of value." );
        try{
            auto intValue = std::stoi( value );
            data.config.addValue( data.name, intValue );
        }catch( std::invalid_argument& ){
            throw std::string( "Cannot convert \"" + value + "\" to int." );
        }
    }},

    {"float", typeid(float).hash_code(), [](VariableLoadData&& data){
        auto value = loadWord( data.file, "Unexpected EOF instead of value." );
        try{
            auto floatValue = std::stof( value );
            data.config.addValue( data.name, floatValue );
        }catch( std::invalid_argument& ){
            throw std::string( "Cannot convert \"" + value + "\" to float." );
        }
    }},

    {"string", typeid(std::string).hash_code(), [](VariableLoadData&& data){
        std::string value, nextWord;
        value = loadWord( data.file, "Unexpected EOF instead of value." );
        if( value.empty() || value[0] != '\"' )
            throw std::string( "string should begin with \" char." );
        while( *(value.end() - 1) != '\"' ){
            data.file >> nextWord;
            if( !data.file.good() )
                throw std::string( "Unclosed string." );
            value += (' ' + nextWord);
        }
        data.config.addValue( data.name, value.substr( 1, value.size() - 2 ) );
    }},

    {"bool", typeid(bool).hash_code(), [](VariableLoadData&& data){
        auto value = loadWord( data.file, "Unexpected EOF instead of value." );
        data.config.addValue( data.name, [&](){
            if( value == "true" )
                return true;
            else if( value == "false" )
                return false;
            else
                throw std::string( R"(bool should be "true", or "false", not ")" + value + R"(".)" );
        }());
    }},

    {"block", typeid(Config).hash_code(), [](VariableLoadData&& data){
        data.config.addValue( data.name, Config{data.config._scope, data.name, data.file} );
    }}
/*, // Unfinished feature - zawieszone
    {"array", typeid(ConfigArray).hash_code(), [](VariableLoadData&& data){
        auto word = loadWord( data.file, "Unexpected EOF instead of type for array." );
        struct ArrayField{ConfigType type; std::string name;};
        std::vector<ArrayField> arrayContent;
        if( word == "{" ){
            while((word = loadWord(data.file, "Unexpected EOF instead of type for array." )) != "}"){
                auto type = getType( word );
                if( type == nullptr )
                    throw std::string( "Expected type for array, got \"" + word + "\"." );
                word = loadWord(data.file, "Unexpected EOF instead of name of variable for array." );
                if(word == "}")
                    throw std::string( "Table closed without name for variable" );
                arrayContent.push_back( {*type , word} );
            }
        }else{
            auto type = getType( word );
            if( type == nullptr )
                throw std::string( "Expected type for array, got \"" + word + "\"." );
            arrayContent.push_back( {*type, ""} );
        }
        auto i = 0;
        for(const auto& type : arrayContent){
            while( true ){ // nie wiem, no nie pasuje mi tu tamten warunek
                auto posBeforeWord = data.file.tellg();
                word = loadWord( data.file, "Unexpected EOF instead of value in array." );

                if( word == "end" )
                    break;

                data.file.seekg( posBeforeWord );

                auto name = data.name + '[' + std::to_string( i ) + ']';
                type.func( VariableLoadData{data.config, name, data.file} );
                i++;
            }
            auto name = data.name + ".size";
            data < int >.insert( {name, i} );
        }
    }}
*/
};

// @formatter:on

Config::Config(const std::string& filename):
    _scope( filename.substr( 0, filename.rfind( '.' ) ) + '.' ){
    loadFile( filename );
}

Config::Config(const std::string& parentName, const std::string& scope, std::ifstream& file):
    _scope( parentName + scope + '.' ){
    loadConfig( file );
}

bool Config::loadFile(const std::string& filename){
    std::ifstream file;
    file.open( filename );
    if( !file.good() ){
        warning( "Cannot open configuration file: \"" + filename + '\"' );
        return false;
    }
    return loadConfig( file );
}

bool Config::loadConfig(std::ifstream& file){
    std::string loadedType, name;
    while( file.good() ){
        try{
            loadedType = loadWord( file, "Unexpected EOF instead of type." );

            if( loadedType == "end" )
                return true;

            name = loadWord( file, "Unexpected EOF instead of variable name." );

            auto foundType = getType( loadedType );

            if( foundType )
                foundType->func( VariableLoadData{*this, name, file} );
            else
                throw std::string( "Expected type, got \"" + loadedType + "\"." );
        }
        catch( const std::string& error ){
            warning(
                "Error loading config file:\n" + error + "\nin variable \"" + _scope + name +
                "\".\n\nLoaded data may be invalid."
            );
            continue;
        }
    }
}

std::string Config::loadWord(std::ifstream& file, const std::string& errorMsg){
    std::string loadedValue;
    file >> loadedValue;
    if( !file.good() )
        throw errorMsg;
    if( loadedValue[0] == '#' ){
        while( file.get() != '\n' )
            if( !file.good() )
                throw std::string( "Unexpected EOF in comment." );
        loadedValue = loadWord( file, errorMsg );
    }
    return loadedValue;
}

const Config::ConfigType* Config::getType(const std::string name){
    auto foundType = std::find_if(
        types.begin(), types.end(), [&name](auto& type){
            return type.name == name;
        }
    );
    if( foundType != types.end() )
        return foundType.base();
    else
        return nullptr;
}

const Config::ConfigType* Config::getType(std::size_t typeId){
    auto foundType = std::find_if(
        types.begin(), types.end(), [&typeId](auto& type){
            return type.typeId == typeId;
        }
    );
    if( foundType != types.end() )
        return foundType.base();
    else
        return nullptr;
}

