//
// Created by stefko on 5/15/26.
//

#include "Hangar.h"
#include <stdexcept>

Hangar::Hangar(std::string hangarId, const int capacity, const double fee)
    : hangarId(std::move(hangarId)), capacity(capacity), fee(fee) {
    if (this->hangarId.empty())
        throw std::invalid_argument("Hangar ID cannot be empty.");
    if (capacity <= 0)
        throw std::invalid_argument("Capacity must be greater than zero.");
    if (fee < 0)
        throw std::invalid_argument("Repair fee cannot be negative.");
}
