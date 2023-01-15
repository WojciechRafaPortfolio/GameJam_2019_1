#pragma once

#include <string>
// extern Global <GameConfig> config;

void warning(const std::string& messageStr);
[[noreturn]] void fatalError(const std::string& messageStr);
void message(std::string windowName, const std::string& message);
