#pragma once

#include "users/Passenger.h"
#include <ostream>


class SaveUserFundsVisitor : public UserVisitor {
        std::ostream &out;

    public:
        explicit SaveUserFundsVisitor(std::ostream &os);

        void visit(Passenger &p) override;
    };


