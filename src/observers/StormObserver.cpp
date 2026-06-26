#include "StormObserver.h"
#include "core/Engine.h"
#include "operations/Airline.h"
#include "operations/Flight.h"
#include "facilities/Runway.h"
#include <print>

StormObserver::StormObserver(Engine &engine) : engine(engine) {
}

void StormObserver::onWeatherChanged(const WeatherCondition newCondition) {
    if (newCondition != WeatherCondition::Storm) return;
    std::println("[Observer] Verifying airport infrastructure for safe landing conditions...");
    bool hasActiveILS = false;
    std::string maintenanceRunwayId;
    for (const auto &r: engine.getRunways()) {
        if (r->hasILS() && r->getRunwayStatus() != RunwayStatus::Maintenance) {
            hasActiveILS = true;
            break;
        }
        if (r->getRunwayStatus() == RunwayStatus::Maintenance && maintenanceRunwayId.empty()) {
            maintenanceRunwayId = r->getRunwayId();
        }
    }
    if (hasActiveILS) {
        std::println("[Observer] All flights are safe to continue (ILS-equipped runway available).");
        return;
    }
    if (!maintenanceRunwayId.empty()) {
        std::println("[System] WARNING: No active runways with ILS available! ({} is currently in Maintenance).",
                     maintenanceRunwayId);
    } else {
        std::println("[System] WARNING: No active runways with ILS available!");
    }
    for (const auto &airline: engine.getAirlines()) {
        for (auto f: airline->getAllFlights()) {
            const auto st = f->getFlightStatus();
            if (st != FlightStatus::Scheduled && st != FlightStatus::Delayed && st != FlightStatus::Boarding) continue;
            std::println("[Observer] Flight {} Cancelled due to severe weather!", f->getFlightId());
            f->setFlightStatus(FlightStatus::Cancelled);
            std::println("[System] Auto-refunding passengers for flight {}...", f->getFlightId());
            engine.refundAllPassengersForFlight(f->getFlightId());
            if (st == FlightStatus::Boarding) {
                auto it = std::ranges::find_if(engine.getRunways(), [&](const auto &r) {
                    return r->getAssignedAirplane() == f->getAirplane();
                });
                if (it != engine.getRunways().end()) (*it)->free();
            }
        }
    }
}


