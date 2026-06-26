#pragma once

#include <expected>
#include <memory>
#include <string>

class Flight;
class Airplane;

enum class RunwayStatus {
    Free,
    Occupied,
    Maintenance
};

[[nodiscard]] std::string runwayStatusToString(RunwayStatus status) noexcept;

[[nodiscard]] RunwayStatus stringToRunwayStatus(const std::string &str);

class Runway {
    std::string runwayId;
    double runwayLength{0.0};
    RunwayStatus runwayStatus;
    bool ILS{false};
    bool VIPTerminal{false};
    bool heavyDuty{false};
    std::weak_ptr<Airplane> assignedAirplane;

public:
    Runway(std::string runwayId, double runwayLength, bool hasILS, bool hasVIPTerminal, bool hasHeavyDuty);

    [[nodiscard]] const std::string &getRunwayId() const;

    [[nodiscard]] double getRunwayLength() const;

    [[nodiscard]] RunwayStatus getRunwayStatus() const;

    [[nodiscard]] bool hasILS() const;

    [[nodiscard]] bool hasVIPTerminal() const;

    [[nodiscard]] bool hasHeavyDuty() const;

    [[nodiscard]] std::shared_ptr<Airplane> getAssignedAirplane() const;

    [[nodiscard]] bool isAvailable() const;

    std::expected<void, std::string> assign(const std::shared_ptr<Airplane> &airplane);

    std::expected<std::shared_ptr<Airplane>, std::string> free();

    std::expected<std::shared_ptr<Airplane>, std::string> closeForMaintenance();

    std::expected<void, std::string> reopen();
};
