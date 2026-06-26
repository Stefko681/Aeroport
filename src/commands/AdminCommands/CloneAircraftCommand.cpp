#include "CloneAircraftCommand.h"
#include <print>
#include "core/Engine.h"

CloneAircraftCommand::CloneAircraftCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole CloneAircraftCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> CloneAircraftCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 3) return std::unexpected("Usage: clone-aircraft [id] [count]");
    int sourceId{0};
    int count{0};
    try {
        sourceId = std::stoi(args[1]);
        count = std::stoi(args[2]);
    } catch (...) {
        return std::unexpected("[Error] Invalid aircraft ID or count.");
    }
    const auto source = engine.findAirplaneGlobal(sourceId);
    if (!source) return std::unexpected("[Error] Aircraft not found.");
    const auto airline = engine.findAirlineOfAircraft(source);
    if (!airline) return std::unexpected("[Error] Airline not found.");
    std::shared_ptr<Airplane> lastCloned;
    for (int i = 0; i < count; ++i) {
        auto result = airline->cloneAircraft(sourceId);
        if (!result) return std::unexpected(result.error());
        lastCloned = std::move(*result);
    }
    std::println("[System] Aircraft ID: {} successfully cloned. New Aircraft ID: {}. {} balance: {:.2f} EUR.", sourceId,
                 lastCloned ? lastCloned->getAirplaneId() : -1, airline->getName(), airline->getBalance());
    return {};
}
