#include "SetWeatherCommand.h"
#include "core/Engine.h"
#include "observers/WeatherSubject.h"
#include <print>
#include <algorithm>

SetWeatherCommand::SetWeatherCommand(Engine &engine) : CLICommand(engine) {
}

std::expected<void, std::string> SetWeatherCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: set-weather [Sunny|Raining|Storm]");
    std::string w = args[1];
    std::ranges::transform(w, w.begin(), ::toupper);
    WeatherCondition newState;
    if (w == "SUNNY") newState = WeatherCondition::Sunny;
    else if (w == "RAINING") newState = WeatherCondition::Raining;
    else if (w == "STORM") newState = WeatherCondition::Storm;
    else return std::unexpected("[Error] Unknown weather. Use Sunny | Raining | Storm.");
    std::println("[ALERT] Global Weather Conditions changed to {}!", w);
    engine.getWeatherSubject()->notifyAll(newState);
    return {};
}

CommandRole SetWeatherCommand::getRequiredRole() const {
    return CommandRole::Admin;
}
