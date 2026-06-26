#include "Hangar.h"
#include <algorithm>
#include <stdexcept>
#include <ranges>

Hangar::Hangar(std::string hangarId, const int hangarCapacity, const double hangarFee) : hangarId(std::move(hangarId)),
    hangarCapacity(hangarCapacity), hangarFee(hangarFee) {
    if (this->hangarId.empty()) throw std::invalid_argument("Hangar ID cannot be empty.");
    if (hangarCapacity <= 0) throw std::invalid_argument("Capacity must be greater than zero.");
    if (hangarFee < 0) throw std::invalid_argument("Repair fee cannot be negative.");
}

int Hangar::getHangarCapacity() const {
    return hangarCapacity;
}

int Hangar::getHangarOccupancy() const {
    return static_cast<int>(occupants.size());
}

const std::string &Hangar::getHangarId() const {
    return hangarId;
}

double Hangar::getHangarFee() const {
    return hangarFee;
}

bool Hangar::isEmpty() const {
    return occupants.empty();
}

bool Hangar::isFull() const {
    return getHangarOccupancy() >= hangarCapacity;
}

std::vector<std::shared_ptr<Airplane> > Hangar::getHangarOccupants() const {
    std::vector<std::shared_ptr<Airplane> > lockedOccupants;
    for (const auto &weakPlane: occupants) {
        if (auto plane = weakPlane.lock()) lockedOccupants.push_back(plane);
    }
    return lockedOccupants;
}

bool Hangar::contains(const std::shared_ptr<Airplane> &airplane) const {
    if (!airplane) return false;
    auto it = std::ranges::find_if(occupants, [&airplane](const std::weak_ptr<Airplane> &weakPlane) {
        return weakPlane.lock() == airplane;
    });
    return it != occupants.end();
}

std::expected<void, std::string> Hangar::admit(const std::shared_ptr<Airplane> &airplane) {
    if (!airplane) return std::unexpected("Airplane cannot be null");
    if (isFull())return std::unexpected(std::format("Hangar {} is at maximum capacity ({}/{} slots occupied)!",
                                                    hangarId, getHangarOccupancy(), hangarCapacity));
    if (contains(airplane)) return std::unexpected(
        "Aircraft " + std::to_string(airplane-> getAirplaneId()) + " is already in hangar " + hangarId + ".");
    occupants.push_back(airplane);
    airplane->setInHangar();
    return {};
}

std::expected<void, std::string> Hangar::release(const std::shared_ptr<Airplane> &airplane) {
    if (!airplane) return std::unexpected("Airplane cannot be null");
    const auto it = std::ranges::find_if(occupants, [&airplane](const std::weak_ptr<Airplane> &weakPlane) {
        return weakPlane.lock() == airplane;
    });
    if (it == occupants.end()) return std::unexpected(
        "Aircraft " + std::to_string(airplane->getAirplaneId()) + " is not in hangar " + hangarId + ".");
    occupants.erase(it);
    airplane->restoreAirplaneHealth();
    airplane->setInHangar();
    return {};
}

std::expected<void, std::string> Hangar::loadOccupant(const std::shared_ptr<Airplane> &airplane) {
    if (!airplane) return std::unexpected("Airplane cannot be null.");
    occupants.push_back(airplane);
    return {};
}
