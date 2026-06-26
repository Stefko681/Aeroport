#pragma once



#include "commands/DispatcherCommand.h"
#include "operations/Airline.h"
#include "operations/Flight.h"

class DelayFlightCommand final : public DispatcherCommand {
    std::shared_ptr<Flight> flight;
    std::string reason;
    FlightStatus prevStatus{FlightStatus::Scheduled};

public:
    explicit DelayFlightCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    void undo() override;

    [[nodiscard]] std::string description() const override;
};
