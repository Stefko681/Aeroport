//
// Created by stefko on 5/15/26.
//

#include "Runway.h"
#include <stdexcept>

#include "airplanes/Airplane.h"
#include "operations/Flight.h"

Runway::Runway(std::string runwayId, const double runwayLength, const bool hasILS, const bool hasVIPTerminal,
               const bool hasHeavyDuty) : runwayId(std::move(runwayId)), runwayLength(runwayLength),
                                          runwayStatus(RunwayStatus::Free), ILS(hasILS),
                                          VIPTerminal(hasVIPTerminal), heavyDuty(hasHeavyDuty) {
    if (this->runwayId.empty()) throw std::invalid_argument("Runway ID cannot be empty.");
    if (runwayLength <= 0) throw std::invalid_argument("Runway length must be positive.");
}

const std::string &Runway::getRunwayId() const {
    return runwayId;
}

double Runway::getRunwayLength() const {
    return runwayLength;
}

RunwayStatus Runway::getRunwayStatus() const {
    return runwayStatus;
}

bool Runway::hasILS() const {
    return ILS;
}

bool Runway::hasVIPTerminal() const {
    return VIPTerminal;
}

bool Runway::hasHeavyDuty() const {
    return heavyDuty;
}

std::shared_ptr<Airplane> Runway::getAssignedAirplane() const {
    return assignedAirplane.lock();
}

bool Runway::isAvailable() const {
    return runwayStatus == RunwayStatus::Free;
}

std::expected<void, std::string> Runway::assign(const std::shared_ptr<Airplane> &airplane) {
    if (!airplane) return std::unexpected("Airplane cannot be null.");
    if (runwayStatus != RunwayStatus::Free)
        return std::unexpected(
            "Runway " + runwayId + " is not Free and cannot be assigned.");
    assignedAirplane = airplane;
    runwayStatus = RunwayStatus::Occupied;
    return {};
}

std::expected<std::shared_ptr<Airplane>, std::string> Runway::free() {
    if (runwayStatus != RunwayStatus::Occupied)
        return std::unexpected(
            "Runway " + runwayId + " is not Occupied; nothing to free.");
    auto released = assignedAirplane.lock();
    assignedAirplane.reset();
    runwayStatus = RunwayStatus::Free;
    return released;
}

std::expected<std::shared_ptr<Airplane>, std::string> Runway::closeForMaintenance() {
    if (runwayStatus == RunwayStatus::Maintenance)
        return std::unexpected(
            "Runway " + runwayId + " is already in Maintenance.");
    auto released = assignedAirplane.lock();
    assignedAirplane.reset();
    runwayStatus = RunwayStatus::Maintenance;
    return released;
}

std::expected<void, std::string> Runway::reopen() {
    if (runwayStatus != RunwayStatus::Maintenance)
        return std::unexpected(
            "Runway " + runwayId + " is not in Maintenance and cannot be reopened.");
    runwayStatus = RunwayStatus::Free;
    return {};
}

std::string runwayStatusToString(RunwayStatus status) noexcept {
    switch (status) {
        case RunwayStatus::Free: return "Free";
        case RunwayStatus::Occupied: return "Occupied";
        case RunwayStatus::Maintenance: return "Maintenance";
    }
    return "Unknown";
}

RunwayStatus stringToRunwayStatus(const std::string &str) {
    if (str == "Free") return RunwayStatus::Free;
    if (str == "Occupied") return RunwayStatus::Occupied;
    if (str == "Maintenance") return RunwayStatus::Maintenance;
    throw std::invalid_argument("Invalid RunwayStatus string.");
}
