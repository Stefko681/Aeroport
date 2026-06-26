#include "MyTicketsCommand.h"
#include "visitors/PassengerVisitors/MyTicketsVisitor.h"

MyTicketsCommand::MyTicketsCommand(Engine &engine) : CLICommand(engine) {
}

std::expected<void, std::string> MyTicketsCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 1) return std::unexpected("Usage: my-tickets");
    MyTicketsVisitor visitor;
    engine.getCurrentUser()->accept(visitor);
    return {};
}

CommandRole MyTicketsCommand::getRequiredRole() const {
    return CommandRole::Passenger;
}
