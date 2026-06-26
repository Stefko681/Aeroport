#include "BuyAircraftCommand.h"
#include <print>
#include <ranges>

#include "core/Engine.h"
#include "airplanes/AirplaneFactory.h"
#include "operations/Airline.h"

BuyAircraftCommand::BuyAircraftCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole BuyAircraftCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> BuyAircraftCommand::execute(const std::vector<std::string> &args) {
    if (args.size() < 5) return std::unexpected("Usage: buy-aircraft [airline] [type] [model] [cap]");
    const auto airline = engine.findAirline(args[1]);
    if (!airline) return std::unexpected("[Error] Airline not found.");
    size_t capacity;
    try {
        capacity = std::stoull(args.back());
    } catch (...) {
        return std::unexpected("[Error] Invalid capacity/tonnage value.");
    }
    auto modelArgs = std::views::counted(args.begin() + 3, args.size() - 4);
    const std::string model = modelArgs | std::views::join_with(' ') | std::ranges::to<std::string>();
    std::unique_ptr<Airplane> plane;
    try {
        plane = AirplaneFactory::create(args[2], model, capacity);
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    const int newId = plane->getAirplaneId();
    if (auto result = airline->purchaseAircraft(std::shared_ptr<Airplane>(std::move(plane))); !result) return
            std::unexpected(result.error());
    std::println("[System] Purchased {} (ID: {}). {} balance: {:.2f} EUR.", args[2], newId, airline->getName(),
                 airline->getBalance());
    return {};
}
