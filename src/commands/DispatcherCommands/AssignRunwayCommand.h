#pragma once


#include "commands/DispatcherCommand.h"
#include "facilities/Runway.h"
#include "operations/Flight.h"

class AssignRunwayCommand final : public DispatcherCommand {
    std::shared_ptr<Runway> runway;
    std::shared_ptr<Flight> flight;
    FlightStatus prevFlightStatus{FlightStatus::Scheduled};

public:
    explicit AssignRunwayCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    void undo() override;

    [[nodiscard]] std::string description() const override;
};

