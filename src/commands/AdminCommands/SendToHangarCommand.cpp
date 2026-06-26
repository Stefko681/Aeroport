#include "SendToHangarCommand.h"
#include <print>
#include "core/Engine.h"
#include "facilities/Hangar.h"
#include "operations/Airline.h"

SendToHangarCommand::SendToHangarCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole SendToHangarCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> SendToHangarCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 3) return std::unexpected("Usage: send-to-hangar [aircraft_id] [hangar_id]");
    int aircraftId{0};
    try {
        aircraftId = std::stoi(args[1]);
    } catch (...) {
        return std::unexpected("[Error] Invalid aircraft ID.");
    }
    const auto plane = engine.findAirplaneGlobal(aircraftId);
    const auto hangar = engine.findHangar(args[2]);
    if (!plane || !hangar) return std::unexpected("[Error] Aircraft or Hangar not found.");
    if (hangar->isFull())
        return std::unexpected(std::format("[Error] Hangar {} is at maximum capacity ({}/{} slots occupied)!",
                                           hangar->getHangarId(), hangar->getHangarOccupancy(),
                                           hangar->getHangarCapacity()));
    const auto airline = engine.findAirlineOfAircraft(plane);
    if (!airline) return std::unexpected("[Error] Airline not found.");
    const double fee = hangar->getHangarFee();
    if (auto balanceRes = airline->deductBalance(fee); !balanceRes) return std::unexpected(balanceRes.error());
    hangar->admit(plane);
    std::println("[Success] Aircraft ID: {} admitted to Hangar {}. {:.2f} EUR deducted from {} balance.",
                 plane->getAirplaneId(), hangar->getHangarId(), fee, airline->getName());
    return {};
}
