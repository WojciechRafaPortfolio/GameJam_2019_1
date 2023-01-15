#pragma once

#include <map>
#include <vector>
#include <string>
#include <functional>
#include <typeinfo>

class Config{
public:
    Config(const std::string& filename);

    template <typename T = Config>
    T&& get(const std::string& name);

private:
    Config(const std::string& parentName, const std::string& scope, std::ifstream& file);

    const std::string _scope;

    bool loadFile(const std::string& filename);

    bool loadConfig(std::ifstream& file);

    static std::string loadWord(std::ifstream&, const std::string& errorMsg);

    struct VariableLoadData{
        Config& config;
        std::string& name;
        std::ifstream& file;
    };

    struct ConfigType{
        std::string name;
        std::size_t typeId;
        std::function<void(VariableLoadData&&)> func;
    };

    template <typename T>
    static std::map<std::string, T> data;
    static const std::vector< ConfigType> types;

    static const ConfigType* getType(const std::string name);
    static const ConfigType* getType(std::size_t typeId);

    template <typename T>
    void addValue(const std::string& name, T&& value);
};

#include "Config.inl"
