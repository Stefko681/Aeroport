#pragma once

#include <expected>
#include <string>
#include <vector>
#include "airplanes/Airplane.h"
#include <format>

class Hangar {
protected:
    std::string hangarId;
    int hangarCapacity{0};
    double hangarFee;
    std::vector<std::weak_ptr<Airplane> > occupants;

public:
    Hangar(std::string hangarId, int hangarCapacity, double hangarFee);

    [[nodiscard]] const std::string &getHangarId() const;

    [[nodiscard]] int getHangarCapacity() const;

    [[nodiscard]] double getHangarFee() const;

    [[nodiscard]] std::vector<std::shared_ptr<Airplane> > getHangarOccupants() const;

    [[nodiscard]] int getHangarOccupancy() const;

    [[nodiscard]] bool isFull() const;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] bool contains(const std::shared_ptr<Airplane> &airplane) const;

    std::expected<void, std::string> admit(const std::shared_ptr<Airplane>& airplane);

    std::expected<void, std::string> release(const std::shared_ptr<Airplane> &airplane);

    std::expected<void, std::string> loadOccupant(const std::shared_ptr<Airplane>& airplane);
};




