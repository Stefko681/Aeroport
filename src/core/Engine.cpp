#include "Engine.h"
#include "commands/DispatcherCommand.h"
#include "observers/WeatherSubject.h"
#include "observers/StormObserver.h"
#include "users/AirportAuthority.h"
#include "users/Passenger.h"
#include "operations/Airline.h"
#include "operations/Flight.h"
#include "airplanes/Airplane.h"
#include "facilities/Runway.h"
#include "facilities/Hangar.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <print>
#include <ranges>
#include "commands/CommandFactory.h"
#include "../visitors/UserVisitors/RefundVisitor.h"

namespace {
    std::vector<std::string> tokenize(const std::string &line) {
        std::istringstream iss(line);
        return {
            std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}
        };
    }
}

Engine::Engine() {
    auto admin = std::make_unique<AirportAuthority>("admin", "admin");
    users.emplace("admin", std::move(admin));
    weatherSubject = std::make_unique<WeatherSubject>();
    stormObserver = std::make_unique<StormObserver>(*this);
    weatherSubject->subscribe(stormObserver);
}

Engine &Engine::getInstance() {
    static Engine instance;
    return instance;
}

void Engine::run() {
    std::string line;
    while (running) {
        std::print("> ");
        std::fflush(stdout);
        if (!std::getline(std::cin, line)) break;
        const auto tokens = tokenize(line);
        if (tokens.empty()) continue;
        if (auto result = dispatch(tokens); !result)
            std::println("[Error] {}", result.error());
    }
}

std::expected<void, std::string> Engine::dispatch(const std::vector<std::string> &tokens) {
    if (tokens.empty()) return {};
    const std::shared_ptr cmd(CommandFactory::create(tokens[0], *this));
    if (!cmd) return std::unexpected("Unknown command: '" + tokens[0] + "'. Type 'help' to see available commands.");
    const CommandRole reqRole = cmd->getRequiredRole();
    const auto activeUser = currentUser.lock();
    if (reqRole == CommandRole::Guest && activeUser)
        return std::unexpected("Another user is already logged in. Type 'logout' first.");
    if (reqRole != CommandRole::Any && reqRole != CommandRole::Guest) {
        if (!activeUser) return std::unexpected("You must log in first.");
        bool roleMatch = false;
        switch (reqRole) {
            case CommandRole::Passenger: roleMatch = (activeUser->getUserRole() == UserRole::Passenger);
                break;
            case CommandRole::Dispatcher: roleMatch = (activeUser->getUserRole() == UserRole::TrafficControl);
                break;
            case CommandRole::Admin: roleMatch = (activeUser->getUserRole() == UserRole::AirportAuthority);
                break;
            default: break;
        }
        if (!roleMatch) return std::unexpected("You do not have permission to use this command.");
    }
    const bool undoable = cmd->isUndoable();
    if (auto result = cmd->execute(tokens); !result)
        std::println("[Error] {}", result.error());
    else if (undoable)
        commandHistory.push_back(cmd);
    return {};
}

std::shared_ptr<Airline> Engine::findAirline(const std::string &name) const {
    const auto it = std::ranges::find_if(airlines, [&](const auto &airplane) {
        return airplane->getName() == name;
    });
    return it != airlines.end() ? *it : nullptr;
}

std::shared_ptr<Runway> Engine::findRunway(const std::string &id) const {
    const auto it = std::ranges::find_if(runways, [&](const auto &runway) {
        return runway->getRunwayId() == id;
    });
    return it != runways.end() ? *it : nullptr;
}

std::shared_ptr<Hangar> Engine::findHangar(const std::string &id) const {
    const auto it = std::ranges::find_if(hangars, [&](const auto &hangar) {
        return hangar->getHangarId() == id;
    });
    return it != hangars.end() ? *it : nullptr;
}

std::shared_ptr<Hangar> Engine::findHangarOf(const std::shared_ptr<Airplane> &airplane) const {
    if (!airplane) return nullptr;
    const auto it = std::ranges::find_if(hangars, [&](const auto &h) {
        return h->contains(airplane);
    });
    return it != hangars.end() ? *it : nullptr;
}

std::shared_ptr<Flight> Engine::findFlightGlobal(const std::string &id) const {
    for (const auto &airline: airlines)
        if (auto flight = airline->findFlight(id)) return flight;
    return nullptr;
}

std::shared_ptr<Airline> Engine::findAirlineOfFlight(const std::shared_ptr<Flight> &flight) const {
    const auto it = std::ranges::find_if(airlines, [&](const auto &a) {
        const auto &flights = a->getAllFlights();
        return std::ranges::find(flights, flight) != flights.end();
    });
    return it != airlines.end() ? *it : nullptr;
}

std::shared_ptr<Airline> Engine::findAirlineOfAircraft(const std::shared_ptr<Airplane> &airplane) const {
    auto it = std::ranges::find_if(airlines, [&](const auto &a) {
        const auto &fleet = a->getFleet();
        return std::ranges::find(fleet, airplane) != fleet.end();
    });
    return it != airlines.end() ? *it : nullptr;
}

void Engine::refundAllPassengersForFlight(const std::string &flightId) {
    {
        RefundVisitor visitor(flightId);
        for (const auto &user: users | std::views::values) {
            user->accept(visitor);
        }
    }
}

std::shared_ptr<User> Engine::findUser(const std::string &username) const {
    const auto it = users.find(username);
    return (it != users.end()) ? it->second : nullptr;
}

std::shared_ptr<User> Engine::getCurrentUser() const {
    return currentUser.lock();
}

void Engine::setCurrentUser(const std::shared_ptr<User> &user) {
    currentUser = user;
}

void Engine::addUser(const std::shared_ptr<User> &user) {
    if (user) users.emplace(user->getName(), user);
}

const std::vector<std::shared_ptr<Airline> > &Engine::getAirlines() const {
    return airlines;
}

void Engine::addAirline(const std::shared_ptr<Airline> &airline) {
    if (airline) airlines.push_back(airline);
}

void Engine::addRunway(const std::shared_ptr<Runway> &runway) {
    if (runway) runways.push_back(runway);
}

void Engine::addHangar(const std::shared_ptr<Hangar> &hangar) {
    if (hangar) hangars.push_back(hangar);
}

std::shared_ptr<WeatherSubject> Engine::getWeatherSubject() const {
    return weatherSubject;
}

const std::vector<std::shared_ptr<Runway> > &Engine::getRunways() const {
    return runways;
}

void Engine::undoLastCommand() {
    if (commandHistory.empty()) throw std::runtime_error("Nothing to undo.");
    const auto &last = commandHistory.back();
    std::println("[System] Reverting last command ({})...", last->description());
    last->undo();
    commandHistory.pop_back();
}

int Engine::getNextAircraftId() {
    return nextAircraftId++;
}

std::shared_ptr<Airplane> Engine::findAirplaneGlobal(const int id) const {
    for (const auto &airline: airlines)
        if (auto plane = airline->findAirplane(id)) return plane;
    return nullptr;
}

const std::unordered_map<std::string, std::shared_ptr<User> > &Engine::getUsers() const {
    return users;
}

const std::vector<std::shared_ptr<Hangar> > &Engine::getHangars() const {
    return hangars;
}

void Engine::clearAllData() {
    users.clear();
    airlines.clear();
    runways.clear();
    hangars.clear();
    commandHistory.clear();
}

void Engine::setNextAircraftId(int id) {
    nextAircraftId = id;
}
