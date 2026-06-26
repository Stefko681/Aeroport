//
// Created by stefko on 5/25/26.
//

#include "DispatcherCommand.h"

DispatcherCommand::DispatcherCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole DispatcherCommand::getRequiredRole() const {
    return CommandRole::Dispatcher;
}

