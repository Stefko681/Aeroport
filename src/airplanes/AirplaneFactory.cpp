#include "AirplaneFactory.h"
#include "CargoPlane.h"
#include "PassengerPlane.h"
#include "PrivateJet.h"

std::unique_ptr<Airplane> AirplaneFactory::create(const std::string &type, std::string model,
                                                  size_t capacity) {
    if (type == "PassengerPlane") return std::make_unique<PassengerPlane>(
        std::move(model), 100.0, capacity);
    if (type == "CargoPlane") return std::make_unique<CargoPlane>(std::move(model), 100.0, capacity);
    if (type == "PrivateJet") return std::make_unique<PrivateJet>(std::move(model), 100.0);
    throw std::runtime_error("Unknown aircraft type '" + type + "'. Use PassengerPlane | CargoPlane | PrivateJet.");
}
