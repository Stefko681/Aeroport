#include "SaveManager.h"
#include "core/Engine.h"
#include "users/User.h"
#include "users/Passenger.h"
#include "users/TrafficControl.h"
#include "users/AirportAuthority.h"
#include "operations/Airline.h"
#include "operations/Flight.h"
#include "airplanes/Airplane.h"
#include "airplanes/PassengerPlane.h"
#include "airplanes/CargoPlane.h"
#include "airplanes/PrivateJet.h"
#include "facilities/Runway.h"
#include "facilities/Hangar.h"
#include "tickets/Ticket.h"
#include "visitors/TicketVisitors/LoadTicketVisitor.h"
#include <filesystem>
#include <fstream>
#include <ranges>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include "visitors/AirplaneVisitors/SaveAirplaneCapacityVisitor.h"
#include "visitors/SaveVisitors/SaveUserFundsVisitor.h"
#include "visitors/SaveVisitors/SaveUserTicketsVisitor.h"

bool SaveManager::save(Engine &engine, const std::string &path) {
    std::ofstream out(path);
    if (!out) return false;
    out.precision(10);
    out << "[Users]\n";
    for (const auto &user: engine.getUsers() | std::views::values) {
        out << user->getName() << '\t'
                << userRoleToString(user->getUserRole()) << '\t'
                << user->getPassword();
        SaveUserFundsVisitor fundsVisitor(out);
        user->accept(fundsVisitor);
        out << '\n';
    }
    out << "[Airlines]\n";
    for (const auto &a: engine.getAirlines()) {
        out << a->getName() << '\t' << a->getBalance() << '\n';
    }
    out << "[Aircraft]\n";
    for (const auto &a: engine.getAirlines()) {
        for (const auto &p: a->getFleet()) {
            out << a->getName() << '\t'
                    << p->getAirplaneId() << '\t'
                    << airplaneTypeToString(p->getAirplaneType()) << '\t'
                    << p->getAirplaneModel() << '\t'
                    << p->getAirplaneHealth() << '\t';
            SaveAirplaneCapacityVisitor capacityVisitor(out);
            p->accept(capacityVisitor);
            out << '\t' << (p->isInHangar() ? "1" : "0") << '\n';
        }
    }
    out << "[Flights]\n";
    for (const auto &a: engine.getAirlines()) {
        for (const auto &f: a->getAllFlights()) {
            auto plane = f->getAirplane();
            out << a->getName() << '\t'
                    << f->getFlightId() << '\t'
                    << (plane ? plane->getAirplaneId() : -1) << '\t'
                    << f->getDestination() << '\t'
                    << f->getBasePrice() << '\t'
                    << flightStatusToString(f->getFlightStatus()) << '\n';
        }
    }
    out << "[Tickets]\n";
    for (const auto &[name, user]: engine.getUsers()) {
        SaveUserTicketsVisitor ticketVisitor(out, name);
        user->accept(ticketVisitor);
    }
    out << "[Runways]\n";
    for (const auto &r: engine.getRunways()) {
        std::string assignedFlightId = "-";
        if (r->getRunwayStatus() == RunwayStatus::Occupied) {
            if (auto plane = r->getAssignedAirplane()) {
                for (const auto &a: engine.getAirlines()) {
                    for (const auto &f: a->getAllFlights()) {
                        if (f->getFlightStatus() == FlightStatus::Boarding &&
                            f->getAirplane() == plane) {
                            assignedFlightId = f->getFlightId();
                            break;
                        }
                    }
                    if (assignedFlightId != "-") break;
                }
            }
        }
        out << r->getRunwayId() << '\t'
                << r->getRunwayLength() << '\t'
                << (r->hasILS() ? "1" : "0") << '\t'
                << (r->hasVIPTerminal() ? "1" : "0") << '\t'
                << (r->hasHeavyDuty() ? "1" : "0") << '\t'
                << runwayStatusToString(r->getRunwayStatus()) << '\t'
                << assignedFlightId << '\n';
    }
    out << "[Hangars]\n";
    for (const auto &h: engine.getHangars()) {
        out << h->getHangarId() << '\t'
                << h->getHangarCapacity() << '\t'
                << h->getHangarFee() << '\n';
    }
    out << "[HangarOccupants]\n";
    for (const auto &h: engine.getHangars()) {
        for (const auto &p: h->getHangarOccupants()) {
            out << h->getHangarId() << '\t'
                    << p->getAirplaneId() << '\n';
        }
    }
    out << "[End]\n";
    return out.good();
}

bool SaveManager::load(Engine &engine, const std::string &path) {
    if (!std::filesystem::exists(path)) return false;
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Cannot open save file: " + path);
    engine.clearAllData();
    std::unordered_map<int, std::shared_ptr<Airplane> > aircraftById;
    std::unordered_map<std::string, std::shared_ptr<Flight> > flightById;
    std::string line;
    std::string section;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (line.front() == '[' && line.back() == ']') {
            section = line.substr(1, line.size() - 2);
            continue;
        }
        std::vector<std::string> cols;
        std::istringstream iss(line);
        std::string tok;
        while (std::getline(iss, tok, '\t')) cols.push_back(tok);
        if (cols.empty()) continue;
        try {
            if (section == "Users") {
                if (cols.size() < 3) throw std::runtime_error("Bad [Users] row");
                std::shared_ptr<User> u;
                if (cols[1] == "Passenger") {
                    const double funds = (cols.size() >= 4) ? std::stod(cols[3]) : 0.0;
                    u = std::make_shared<Passenger>(cols[0], cols[2], funds);
                } else if (cols[1] == "Dispatcher") {
                    u = std::make_shared<TrafficControl>(cols[0], cols[2]);
                } else if (cols[1] == "Admin") {
                    u = std::make_shared<AirportAuthority>(cols[0], cols[2]);
                } else {
                    throw std::runtime_error("Unknown user role: " + cols[1]);
                }
                engine.addUser(u);
            } else if (section == "Airlines") {
                if (cols.size() < 2) throw std::runtime_error("Bad [Airlines] row");
                engine.addAirline(std::make_shared<Airline>(cols[0], std::stod(cols[1])));
            } else if (section == "Aircraft") {
                if (cols.size() < 7) throw std::runtime_error("Bad [Aircraft] row");
                auto a = engine.findAirline(cols[0]);
                if (!a) throw std::runtime_error("Aircraft refers to missing airline: " + cols[0]);
                const int id = std::stoi(cols[1]);
                const std::string &type = cols[2];
                const std::string &model = cols[3];
                const double health = std::stod(cols[4]);
                const size_t capacity = static_cast<size_t>(std::stod(cols[5]));
                const bool inHangar = (cols[6] == "1");
                std::shared_ptr<Airplane> plane;
                if (type == "PassengerPlane")
                    plane = std::make_shared<PassengerPlane>(model, health, static_cast<int>(capacity));
                else if (type == "CargoPlane")
                    plane = std::make_shared<CargoPlane>(model, health, capacity);
                else if (type == "PrivateJet")
                    plane = std::make_shared<PrivateJet>(model, health);
                else
                    throw std::runtime_error("Unknown aircraft type: " + type);
                plane->airplaneId = id;
                if (inHangar) plane->setInHangar();
                aircraftById[id] = plane;
                if (auto result = a->loadAircraft(plane); !result) throw std::runtime_error(
                    "Failed to load aircraft: " + result.error());
            } else if (section == "Flights") {
                if (cols.size() < 6) throw std::runtime_error("Bad [Flights] row");
                auto a = engine.findAirline(cols[0]);
                if (!a) throw std::runtime_error("Flight refers to missing airline.");
                const int aircraftId = std::stoi(cols[2]);
                auto it = aircraftById.find(aircraftId);
                if (it == aircraftById.end()) throw std::runtime_error(
                    "Flight refers to missing aircraft id: " + cols[2]);
                auto f = a->loadFlight(cols[1], it->second, cols[3], std::stod(cols[4]));
                if (!f) throw std::runtime_error("Failed to load flight: " + f.error());
                (*f)->setFlightStatus(stringToFlightStatus(cols[5]));
                flightById[cols[1]] = *f;
            } else if (section == "Tickets") {
                if (cols.size() < 5) throw std::runtime_error("Bad [Tickets] row");
                auto user = engine.findUser(cols[0]);
                if (!user) throw std::runtime_error("Ticket refers to missing user: " + cols[0]);
                auto flightIt = flightById.find(cols[1]);
                if (flightIt == flightById.end()) throw std::runtime_error(
                    "Ticket refers to missing flight: " + cols[1]);
                LoadTicketVisitor loadVisitor(stringToTicketType(cols[2]), flightIt->second, std::stod(cols[3]),
                                              std::stod(cols[4]));
                user->accept(loadVisitor);
            } else if (section == "Runways") {
                if (cols.size() < 7) throw std::runtime_error("Bad [Runways] row");
                auto r = std::make_shared<Runway>(cols[0], std::stod(cols[1]), cols[2] == "1", cols[3] == "1",
                                                  cols[4] == "1");
                const RunwayStatus status = stringToRunwayStatus(cols[5]);
                if (status == RunwayStatus::Occupied && cols[6] != "-") {
                    auto flightIt = flightById.find(cols[6]);
                    if (flightIt == flightById.end()) throw std::runtime_error(
                        "Runway refers to missing flight: " + cols[6]);
                    auto plane = flightIt->second->getAirplane();
                    if (plane) r->assign(plane);
                } else if (status == RunwayStatus::Maintenance) {
                    r->closeForMaintenance();
                }
                engine.addRunway(r);
            } else if (section == "Hangars") {
                if (cols.size() < 3) throw std::runtime_error("Bad [Hangars] row");
                engine.addHangar(std::make_shared<Hangar>(cols[0], std::stoi(cols[1]), std::stod(cols[2])));
            } else if (section == "HangarOccupants") {
                if (cols.size() < 2) throw std::runtime_error("Bad [HangarOccupants] row");
                auto h = engine.findHangar(cols[0]);
                if (!h) throw std::runtime_error("Occupant refers to missing hangar: " + cols[0]);
                const int aircraftId = std::stoi(cols[1]);
                auto it = aircraftById.find(aircraftId);
                if (it == aircraftById.end()) throw std::runtime_error(
                    "Occupant refers to missing aircraft id: " + cols[1]);
                h->loadOccupant(it->second);
            }
        } catch (const std::exception &ex) {
            throw std::runtime_error("Parse error in section [" + section + "]: " + ex.what());
        }
    }
    if (!engine.findUser("admin"))
        engine.addUser(std::make_shared<AirportAuthority>("admin", "admin"));
    int maxId = 0;
    for (const auto &id: aircraftById | std::views::keys) maxId = std::max(maxId, id);
    Engine::setNextAircraftId(maxId + 1);
    return true;
}
