//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_AIRLINE_H
#define AEROPORT_AIRLINE_H
#include <memory>
#include <string>
#include <vector>

class Airplane;
class Flight;

class Airline {
    std::string name;
    double balance;
    std::vector<std::unique_ptr<Airplane> > airplanes;
    std::vector<std::unique_ptr<Flight> > flights;

    static constexpr double AIRCRAFT_PRICE = 10000.0;

public:
    Airline(std::string name, double balance);

    ~Airline() = default;

    Airline(const Airline &other) = delete;

    Airline &operator=(const Airline &other) = delete;

    Airline(Airline &&other) noexcept = default;

    Airline &operator =(Airline &&other) noexcept = default;

    [[nodiscard]] std::string getName() const;

    [[nodiscard]] double getBalance() const;

    [[nodiscard]] int getAircraftCount() const;

    Airplane *purchaseAircraft(std::unique_ptr<Airplane> plane);

    Airplane *cloneAircraft(const std::string &sourceId, const std::string &newId);

    [[nodiscard]] Airplane *findAirplane(const std::string &id) const;

    void deductBalance(double amount);

    void applyFlightProfit(double netAmount);

    Flight *scheduleFlight(const std::string &flightId, const std::string &aircraftId, const std::string &destination,
                           double basePrice);

    [[nodiscard]] Flight *findFlight(const std::string &flightId) const;

    [[nodiscard]] std::vector<Airplane *> getFleet() const;

    [[nodiscard]] std::vector<Flight *> getAllFlights() const;

    void cancelFlight(const std::string &flightId) const;

    void printFleet() const;

    void printFlightRevenue(const std::string &flightId) const;

    void printAuditReport() const;

    [[nodiscard]] int getDepartedCount() const;

    [[nodiscard]] int getCancelledCount() const;
};


#endif //AEROPORT_AIRLINE_H
