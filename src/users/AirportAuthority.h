#pragma once

#include "User.h"

class AirportAuthority final : public User {
public:
    AirportAuthority(std::string name, std::string password);

    [[nodiscard]] UserRole getUserRole() const override;

    void help() const override;

    void viewProfile() const override;

    void accept(UserVisitor &visitor) override;
};

