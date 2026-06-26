#include "ListRunwaysCommand.h"
#include <print>
#include "core/Engine.h"
#include "operations/Flight.h"

ListRunwaysCommand::ListRunwaysCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole ListRunwaysCommand::getRequiredRole() const { return CommandRole::Dispatcher; }

std::expected<void, std::string> ListRunwaysCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 1) return std::unexpected("Usage: list-runways");
    const auto &runways = engine.getRunways();
    if (runways.empty()) {
        std::println("[Error] No runways available.");
        return {};
    }
    std::println("Airport Runways Overview:");
    for (const auto &r: runways) {
        std::string statusStr;
        switch (r->getRunwayStatus()) {
            case RunwayStatus::Free: statusStr = "Free";
                break;
            case RunwayStatus::Occupied: statusStr = "Occupied";
                break;
            case RunwayStatus::Maintenance: statusStr = "Maintenance";
                break;
        }
        std::string flags;
        auto append = [&](const char *tag) {
            if (!flags.empty()) flags += ", ";
            flags += tag;
        };
        if (r->hasILS()) append("ILS");
        if (r->hasVIPTerminal()) append("VIP");
        if (r->hasHeavyDuty()) append("HeavyDuty");
        if (flags.empty()) flags = "Basic";
        std::println("- {} ({}m, {}) -> Status: {}", r->getRunwayId(), r->getRunwayLength(), flags, statusStr);
    }
    return {};
}
