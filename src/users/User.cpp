//
// Created by stefko on 5/13/26.
//

#include "User.h"

#include <stdexcept>

User::User(std::string name, std::string password) : name(std::move(name)), password(std::move(password)) {
    if (name.empty() || password.empty()) throw std::invalid_argument("Name and password cannot be empty");
}
