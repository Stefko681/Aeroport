#include "ViewProfileCommand.h"
#include "core/Engine.h"
#include "users/User.h"

ViewProfileCommand::ViewProfileCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole ViewProfileCommand::getRequiredRole() const {
    return CommandRole::Any;
}

std::expected<void, std::string> ViewProfileCommand::execute(const std::vector<std::string> &args) {
    if (!engine.getCurrentUser()) return std::unexpected("[Error] You must log in first.");
    engine.getCurrentUser()->viewProfile();
    return {};
}
