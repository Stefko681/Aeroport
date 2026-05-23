//
// Created by stefko on 5/14/26.
//

#include "Airplane.h"
#include <stdexcept>

Airplane::Airplane(std::string airplaneId, std::string model, const double health)
    : airplaneId(std::move(airplaneId)), model(std::move(model)), health(health) {
    if (health < 0 || health > 100)
        throw std::invalid_argument("Health must be between 0 and 100.");
    if (this->airplaneId.empty() || this->model.empty())
        throw std::invalid_argument("Airplane ID and model cannot be empty.");
}

bool Airplane::canFly() const {
    return health > 20.0;
}

const std::string &Airplane::getAirplaneId() const {
    return airplaneId;
}

const std::string &Airplane::getModel() const {
    return model;
}

double Airplane::getHealth() const {
    return health;
}

bool Airplane::isInHangar() const {
    return inHangar;
}

void Airplane::restoreHealth() {
    health = 100.0;
}

void Airplane::setInHangar(const bool value) {
    inHangar = value;
}
