#include "User.h"
#include <stdexcept>

User::User(std::string name, std::string password) : name(std::move(name)), password(std::move(password)) {
    if (this->name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (this->password.empty()) throw std::invalid_argument("Password cannot be empty");
}

const std::string &User::getName() const {
    return name;
}

bool User::checkPassword(const std::string &candidate) const {
    return password == candidate;
}

const std::string &User::getPassword() const {
    return password;
}

std::string userRoleToString(const UserRole role) {
    switch (role) {
        case UserRole::Passenger: return "Passenger";
        case UserRole::TrafficControl: return "Dispatcher";
        case UserRole::AirportAuthority: return "Admin";
    }
    return "Unknown";
}

UserRole stringToUserRole(const std::string &str) {
    if (str == "Passenger") return UserRole::Passenger;
    if (str == "Dispatcher") return UserRole::TrafficControl;
    if (str == "Admin") return UserRole::AirportAuthority;
    throw std::invalid_argument("Invalid UserRole string.");
}
