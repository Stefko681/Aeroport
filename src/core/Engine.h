#pragma once

#include "users/User.h"
#include "operations/Airline.h"
#include "facilities/Runway.h"
#include "facilities/Hangar.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "commands/CLICommand.h"

class DispatcherCommand;
class WeatherSubject;
class StormObserver;
class Flight;
class Airplane;

class Engine {
    std::unordered_map<std::string, std::shared_ptr<User> > users;
    std::vector<std::shared_ptr<Airline> > airlines;
    std::vector<std::shared_ptr<Runway> > runways;
    std::vector<std::shared_ptr<Hangar> > hangars;
    std::weak_ptr<User> currentUser;
    static inline int nextAircraftId{1};
    bool running{true};
    std::vector<std::shared_ptr<CLICommand> > commandHistory;
    std::shared_ptr<WeatherSubject> weatherSubject;
    std::shared_ptr<StormObserver> stormObserver;

    Engine();

    std::expected<void, std::string> dispatch(const std::vector<std::string> &tokens);

public:
    Engine(const Engine &other) = delete;

    Engine &operator=(const Engine &other) = delete;

    Engine(Engine &&other) noexcept = delete;

    Engine &operator=(Engine &&other) noexcept = delete;

    static Engine &getInstance();

    [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<User> > &getUsers() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Airline> > &getAirlines() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Runway> > &getRunways() const;

    [[nodiscard]] const std::vector<std::shared_ptr<Hangar> > &getHangars() const;

    [[nodiscard]] std::shared_ptr<User> getCurrentUser() const;

    [[nodiscard]] std::shared_ptr<WeatherSubject> getWeatherSubject() const;

    static int getNextAircraftId();

    static void setNextAircraftId(int id);

    void run();

    void clearAllData();

    [[nodiscard]] std::shared_ptr<User> findUser(const std::string &username) const;

    void setCurrentUser(const std::shared_ptr<User> &user);

    void addUser(const std::shared_ptr<User> &user);

    [[nodiscard]] std::shared_ptr<Airline> findAirline(const std::string &name) const;

    [[nodiscard]] std::shared_ptr<Airline> findAirlineOfFlight(const std::shared_ptr<Flight> &flight) const;

    [[nodiscard]] std::shared_ptr<Airline> findAirlineOfAircraft(const std::shared_ptr<Airplane> &airplane) const;

    [[nodiscard]] std::shared_ptr<Flight> findFlightGlobal(const std::string &id) const;

    [[nodiscard]] std::shared_ptr<Airplane> findAirplaneGlobal(int id) const;

    [[nodiscard]] std::shared_ptr<Runway> findRunway(const std::string &id) const;

    [[nodiscard]] std::shared_ptr<Hangar> findHangar(const std::string &id) const;

    [[nodiscard]] std::shared_ptr<Hangar> findHangarOf(const std::shared_ptr<Airplane> &airplane) const;

    void addAirline(const std::shared_ptr<Airline> &airline);

    void addRunway(const std::shared_ptr<Runway> &runway);

    void addHangar(const std::shared_ptr<Hangar> &hangar);

    void undoLastCommand();

    void refundAllPassengersForFlight(const std::string &flightId);
};