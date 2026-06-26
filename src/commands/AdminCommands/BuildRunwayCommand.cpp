#include "BuildRunwayCommand.h"
#include <print>
#include <ranges>

#include "core/Engine.h"
#include "facilities/RunwayBuilder.h"

BuildRunwayCommand::BuildRunwayCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole BuildRunwayCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> BuildRunwayCommand::execute(const std::vector<std::string> &args) {
    if (args.size() < 3) return std::unexpected("Usage: build-runway [id] [length] [-ils] [-vip] [-heavy]");
    double length;
    try {
        length = std::stod(args[2]);
    } catch (...) {
        return std::unexpected("[Error] Invalid runway length.");
    }
    const std::string &id = args[1];
    RunwayBuilder builder(id, length);
    std::vector<std::string_view> flags;
    for (size_t i = 3; i < args.size(); ++i) {
        if (const auto &arg = args[i]; arg == "-ils" || arg == "ils" || arg == "ILS") {
            builder.withILS();
            flags.emplace_back("ILS");
        } else if (arg == "-vip" || arg == "vip" || arg == "VIP" || arg == "VIPTerminal") {
            builder.withVIPTerminal();
            flags.emplace_back("VIP Terminal");
        } else if (arg == "-heavy" || arg == "heavy" || arg == "HeavyDuty" || arg == "Heavy") {
            builder.withHeavyDuty();
            flags.emplace_back("HeavyDuty");
        }
    }
    const std::string flagStr = flags.empty()
                                    ? "Basic"
                                    : flags | std::views::join_with(std::string_view(", "))
                                      | std::ranges::to<std::string>();

    try {
        engine.addRunway(builder.build());
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    std::println("[System] Runway {} ({}m, {}) built successfully.", id, static_cast<int>(length), flagStr);
    return {};
}
