#pragma once

#include <expected>
#include <memory>
#include <string>
#include <vector>
#include <optional>

class Engine;
class Airplane;
class Flight;

class Airline {
    std::string name;
    double balance{0.0};
    std::vector<std::shared_ptr<Airplane> > airplanes;
    std::vector<std::shared_ptr<Flight> > flights;

    static constexpr double AIRCRAFT_PRICE = 10000.0;

public:
    Airline(std::string name, double balance);

    Airline(const Airline &other) = delete;

    Airline &operator=(const Airline &other) = delete;

    Airline(Airline &&other) noexcept = default;

    Airline &operator=(Airline &&other) noexcept = default;

    ~Airline() = default;

    [[nodiscard]] const std::string &getName() const;

    [[nodiscard]] double getBalance() const;

    [[nodiscard]] std::vector<std::shared_ptr<Airplane> > getFleet() const;

    [[nodiscard]] std::vector<std::shared_ptr<Flight> > getAllFlights() const;

    [[nodiscard]] int getAirplanesCount() const;

    [[nodiscard]] int getDepartedCount() const;

    [[nodiscard]] int getCancelledCount() const;

    [[nodiscard]] std::shared_ptr<Flight> findFlight(const std::string &flightId) const;

    [[nodiscard]] std::shared_ptr<Airplane> findAirplane(int id) const;

    void printFleet() const;

    void printFlightRevenue(const std::string &flightId) const;

    void printAuditReport() const;

    std::expected<void, std::string> deductBalance(double amount);

    void applyFlightProfitDelta(double delta);

    [[nodiscard]] std::expected<std::shared_ptr<Airplane>, std::string> purchaseAircraft(
        std::shared_ptr<Airplane> plane);

    [[nodiscard]] std::expected<std::shared_ptr<Flight>, std::string> scheduleFlight(
        const std::string &flightId, int aircraftId, const std::string &destination, double basePrice);

    [[nodiscard]] std::expected<void, std::string> cancelFlight(const std::string &flightId) const;

    [[nodiscard]] std::expected<std::shared_ptr<Airplane>, std::string> loadAircraft(std::shared_ptr<Airplane> plane);

    [[nodiscard]] std::expected<std::shared_ptr<Flight>, std::string> loadFlight(
        const std::string &flightId, const std::shared_ptr<Airplane> &aircraft, const std::string &destination,
        double basePrice);

    [[nodiscard]] std::expected<std::shared_ptr<Airplane>, std::string> cloneAircraft(int sourceId);
};
