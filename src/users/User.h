//
// Created by stefko on 5/13/26.
//

#ifndef AEROPORT_USER_H
#define AEROPORT_USER_H
#include <string>
#include "UserRole.h"

class User {
protected:
    std::string name;
    std::string password;

public:
    User(std::string name, std::string password);

    virtual ~User() = default;

    virtual UserRole getUserRole() const = 0;

    virtual void logout() const = 0;

    virtual void help() const = 0;

    virtual void viewProfile() const = 0;
};


#endif //AEROPORT_USER_H
