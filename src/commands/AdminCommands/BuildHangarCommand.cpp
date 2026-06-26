#include "BuildHangarCommand.h"
#include <print>
#include "core/Engine.h"

BuildHangarCommand::BuildHangarCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole BuildHangarCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> BuildHangarCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 4) return std::unexpected("Usage: build-hangar [id] [capacity] [repair_fee]");
    try {
        std::string id = args[1];
        int capacity = std::stoi(args[2]);
        double fee = std::stod(args[3]);
        engine.addHangar(std::make_shared<Hangar>(id, capacity, fee));
        std::println("[System] Hangar {} built successfully (Capacity: {}, Repair Fee: {:.2f} EUR).", id, capacity, fee);
        return {};
    } catch (...) {
        return std::unexpected("[Error] Invalid hangar parameters.");
    }
}
