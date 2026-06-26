#pragma once


#include <string>

class Engine;

class SaveManager {
public:
    static constexpr auto DEFAULT_FILE = "aeroport_data.txt";

    static bool save(Engine &engine, const std::string &path = DEFAULT_FILE);

    static bool load(Engine &engine, const std::string &path = DEFAULT_FILE);
};


