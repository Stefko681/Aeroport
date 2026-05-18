//
// Created by stefko on 5/15/26.
//

#include "Airline.h"
#include "Flight.h"
#include <airplanes/Airplane.h>

Airline::Airline(std::string name, const double balance) : name(std::move(name)), balance(balance) {
    if (name.empty()) throw std::invalid_argument("Name cannot be empty");
    if (balance < 0) throw std::invalid_argument("Balance cannot be less than zero");
}
