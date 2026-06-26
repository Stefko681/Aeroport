#pragma once

#include <stdexcept>
#include <string>
#include "../visitors/UserVisitors/UserVisitor.h"

enum class UserRole {
    Passenger,
    TrafficControl,
    AirportAuthority
};

[[nodiscard]] std::string userRoleToString(UserRole role);

[[nodiscard]] UserRole stringToUserRole(const std::string &str);

class User {
protected:
    std::string name;
    std::string password;

public:
    User(std::string name, std::string password);

    virtual ~User() = default;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] const std::string &getPassword() const;

    [[nodiscard]] bool checkPassword(const std::string &candidate) const;

    [[nodiscard]] virtual UserRole getUserRole() const = 0;

    virtual void help() const = 0;

    virtual void viewProfile() const = 0;

    virtual void accept(UserVisitor &visitor) = 0;
};
