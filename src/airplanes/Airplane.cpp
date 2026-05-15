//
// Created by stefko on 5/14/26.
//

#include "Airplane.h"
#include <stdexcept>

Airplane::Airplane(std::string airplaneId, std::string model, const double health) : airplaneId(std::move(airplaneId)),
    model(std::move(model)), health(health) {
    if (health > 100 || health < 0) throw std::invalid_argument("Health can not be less than 0 or more than 100");

    if (airplaneId.empty() || model.empty()) throw std::invalid_argument("Id or model cannot be empty");
}

bool Airplane::canFly() const {
    return health > 20;
}
