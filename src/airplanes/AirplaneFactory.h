#pragma once

#include  <memory>
#include <stdexcept>
#include <string>

class Airplane;

class AirplaneFactory {
public:
    static std::unique_ptr<Airplane> create(const std::string &type, std::string model, size_t capacity);
};


