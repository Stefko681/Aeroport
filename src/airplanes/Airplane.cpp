#include "Airplane.h"
#include "core/Engine.h"

Airplane::Airplane(std::string airplaneModel,
                   const double airplaneHealth) : airplaneId(Engine::getNextAircraftId()),
                                                  airplaneModel(std::move(airplaneModel)),
                                                  airplaneHealth(airplaneHealth) {
    if (airplaneHealth < 0 || airplaneHealth > 100) throw std::invalid_argument("Health must be between 0 and 100.");
    if (this->airplaneModel.empty()) throw std::invalid_argument("Airplane model cannot be empty");
}

bool Airplane::canFly() const {
    return airplaneHealth > 20.0;
}

int Airplane::getAirplaneId() const {
    return airplaneId;
}

const std::string &Airplane::getAirplaneModel() const {
    return airplaneModel;
}

double Airplane::getAirplaneHealth() const {
    return airplaneHealth;
}

bool Airplane::isInHangar() const {
    return inHangar;
}

void Airplane::restoreAirplaneHealth() {
    airplaneHealth = 100.0;
}

void Airplane::setInHangar() {
    inHangar = true;
}

void Airplane::setHealth(const double newHealth) {
    if (newHealth < 0 || newHealth > 100) throw std::invalid_argument("Health must be between 0 and 100.");
    airplaneHealth = newHealth;
}

std::string airplaneTypeToString(AirplaneType type) {
    switch (type) {
        case AirplaneType::PassengerPlane: return "PassengerPlane";
        case AirplaneType::CargoPlane: return "CargoPlane";
        case AirplaneType::PrivateJet: return "PrivateJet";
    }
    return "Unknown";
}

AirplaneType stringToAirplaneType(const std::string &str) {
    if (str == "PassengerPlane") return AirplaneType::PassengerPlane;
    if (str == "CargoPlane") return AirplaneType::CargoPlane;
    if (str == "PrivateJet") return AirplaneType::PrivateJet;
    throw std::invalid_argument("Invalid AirplaneType string.");
}
