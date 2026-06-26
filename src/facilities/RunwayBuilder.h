#pragma once

#include <memory>
#include <string>
#include "Runway.h"

class RunwayBuilder {
    std::string id;
    double length{0.0};
    bool ils{false};
    bool vip{false};
    bool heavy{false};

public:
    RunwayBuilder(std::string id, double length);

    RunwayBuilder &withILS();

    RunwayBuilder &withVIPTerminal();

    RunwayBuilder &withHeavyDuty();

    [[nodiscard]] std::shared_ptr<Runway> build() const;
};


