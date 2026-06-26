#pragma once


#include "commands/DispatcherCommand.h"
#include "facilities/Runway.h"
#include "operations/Airline.h"
#include "operations/Flight.h"

class FreeRunwayCommand final : public DispatcherCommand {
    std::shared_ptr<Runway> runway;
    std::shared_ptr<Flight> flight;
    std::shared_ptr<Airline> airline;
    double prevHealth{0.0};
    double netProfitTransferred{0.0};

public:
    explicit FreeRunwayCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    void undo() override;

    [[nodiscard]] std::string description() const override;
};
