#include "RunwayBuilder.h"
#include <stdexcept>

RunwayBuilder::RunwayBuilder(std::string id, const double length) : id(std::move(id)), length(length) {
    if (this->id.empty()) throw std::invalid_argument("Runway ID cannot be empty.");
    if (length <= 0) throw std::invalid_argument("Runway length must be positive.");
}

RunwayBuilder &RunwayBuilder::withILS() {
    ils = true;
    return *this;
}

RunwayBuilder &RunwayBuilder::withHeavyDuty() {
    heavy = true;
    return *this;
}

RunwayBuilder &RunwayBuilder::withVIPTerminal() {
    vip = true;
    return *this;
}

std::shared_ptr<Runway> RunwayBuilder::build() const {
    return std::make_shared<Runway>(id, length, ils, vip, heavy);
}
