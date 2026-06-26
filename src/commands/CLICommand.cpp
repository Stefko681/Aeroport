#include "CLICommand.h"

CLICommand::CLICommand(Engine &engine) : engine(engine) {
}

bool CLICommand::isUndoable() const {
    return false;
}

void CLICommand::undo() {
}

std::string CLICommand::description() const {
    return "Command";
}
