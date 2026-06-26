//
// Created by stefko on 6/19/26.
//

#include "CommandFactory.h"
#include "DispatcherCommands/AssignRunwayCommand.h"
#include "CLICommand.h"
#include "DispatcherCommands/DelayFlightCommand.h"
#include "DispatcherCommands/FreeRunwayCommand.h"
#include "SystemCommands/HelpCommand.h"
#include "AdminCommands/BuyAircraftCommand.h"
#include "AdminCommands/SetWeatherCommand.h"
#include "AdminCommands/RegisterAirlineCommand.h"
#include "AdminCommands/AirportReportCommand.h"
#include "AdminCommands/AuditAirlineCommand.h"
#include "AdminCommands/BuildHangarCommand.h"
#include "AdminCommands/BuildRunwayCommand.h"
#include "AdminCommands/CancelFlightCommand.h"
#include "AdminCommands/CloneAircraftCommand.h"
#include "AdminCommands/CloseRunwayCommand.h"
#include "AdminCommands/FlightRevenueCommand.h"
#include "AdminCommands/ListFleetCommand.h"
#include "AdminCommands/RetrieveFromHangarCommand.h"
#include "AdminCommands/ScheduleFlightCommand.h"
#include "AdminCommands/SendToHangarCommand.h"
#include "DispatcherCommands/ListAirspaceCommand.h"
#include "DispatcherCommands/ListRunwaysCommand.h"
#include "DispatcherCommands/UndoCommand.h"
#include "SystemCommands/RegisterCommand.h"
#include "SystemCommands/LoadCommand.h"
#include "PassengerCommands/AddBaggageCommand.h"
#include "PassengerCommands/AddFundsCommand.h"
#include "PassengerCommands/BookTicketCommand.h"
#include "PassengerCommands/CancelTicketCommand.h"
#include "PassengerCommands/FilterFlightCommand.h"
#include "PassengerCommands/ListFlightsCommand.h"
#include "PassengerCommands/MyTicketsCommand.h"
#include "PassengerCommands/UpgradeTicketCommand.h"
#include "SystemCommands/LoginCommand.h"
#include "SystemCommands/LogoutCommand.h"
#include "SystemCommands/SaveCommand.h"
#include "SystemCommands/ViewProfileCommand.h"

std::shared_ptr<CLICommand> CommandFactory::create(const std::string &commandName, Engine &engine) {
    if (commandName == "login") return std::make_shared<LoginCommand>(engine);
    if (commandName == "help") return std::make_shared<HelpCommand>(engine);
    if (commandName == "register") return std::make_shared<RegisterCommand>(engine);
    if (commandName == "save") return std::make_shared<SaveCommand>(engine);
    if (commandName == "load") return std::make_shared<LoadCommand>(engine);
    if (commandName == "logout") return std::make_shared<LogoutCommand>(engine);
    if (commandName == "view-profile") return std::make_shared<ViewProfileCommand>(engine);
    if (commandName == "add-funds") return std::make_shared<AddFundsCommand>(engine);
    if (commandName == "list-flights") return std::make_shared<ListFlightsCommand>(engine);
    if (commandName == "filter-flights") return std::make_shared<FilterFlightsCommand>(engine);
    if (commandName == "book-ticket") return std::make_shared<BookTicketCommand>(engine);
    if (commandName == "upgrade-ticket") return std::make_shared<UpgradeTicketCommand>(engine);
    if (commandName == "add-baggage") return std::make_shared<AddBaggageCommand>(engine);
    if (commandName == "cancel-ticket") return std::make_shared<CancelTicketCommand>(engine);
    if (commandName == "my-tickets") return std::make_shared<MyTicketsCommand>(engine);
    if (commandName == "register-airline") return std::make_shared<RegisterAirlineCommand>(engine);
    if (commandName == "buy-aircraft") return std::make_shared<BuyAircraftCommand>(engine);
    if (commandName == "set-weather") return std::make_shared<SetWeatherCommand>(engine);
    if (commandName == "airport-report") return std::make_shared<AirportReportCommand>(engine);
    if (commandName == "assign-runway") return std::make_shared<AssignRunwayCommand>(engine);
    if (commandName == "delay-flight") return std::make_shared<DelayFlightCommand>(engine);
    if (commandName == "free-runway") return std::make_shared<FreeRunwayCommand>(engine);
    if (commandName == "build-runway") return std::make_shared<BuildRunwayCommand>(engine);
    if (commandName == "build-hangar") return std::make_shared<BuildHangarCommand>(engine);
    if (commandName == "close-runway") return std::make_shared<CloseRunwayCommand>(engine);
    if (commandName == "clone-aircraft") return std::make_shared<CloneAircraftCommand>(engine);
    if (commandName == "send-to-hangar") return std::make_shared<SendToHangarCommand>(engine);
    if (commandName == "retrieve-from-hangar") return std::make_shared<RetrieveFromHangarCommand>(engine);
    if (commandName == "schedule-flight") return std::make_shared<ScheduleFlightCommand>(engine);
    if (commandName == "cancel-flight") return std::make_shared<CancelFlightCommand>(engine);
    if (commandName == "flight-revenue") return std::make_shared<FlightRevenueCommand>(engine);
    if (commandName == "list-fleet") return std::make_shared<ListFleetCommand>(engine);
    if (commandName == "audit-airline") return std::make_shared<AuditAirlineCommand>(engine);
    if (commandName == "list-airspace") return std::make_shared<ListAirspaceCommand>(engine);
    if (commandName == "list-runways") return std::make_shared<ListRunwaysCommand>(engine);
    if (commandName == "undo") return std::make_shared<UndoCommand>(engine);
    return {};
}
