#pragma once

#include <memory>
#include <string>

class ConstAirplaneVisitor;
class Runway;
class AirplaneVisitor;

enum class AirplaneType {
    PassengerPlane,
    CargoPlane,
    PrivateJet
};

std::string airplaneTypeToString(AirplaneType type);

[[nodiscard]] AirplaneType stringToAirplaneType(const std::string &str);

class Airplane {
    friend class SaveManager;

protected:
    int airplaneId;
    std::string airplaneModel;
    double airplaneHealth{0.0};
    bool inHangar{false};

public:
    Airplane(std::string airplaneModel, double airplaneHealth);

    virtual ~Airplane() = default;

    [[nodiscard]] int getAirplaneId() const;

    [[nodiscard]] const std::string &getAirplaneModel() const;

    [[nodiscard]] double getAirplaneHealth() const;

    [[nodiscard]] bool isInHangar() const;

    [[nodiscard]] bool canFly() const;

    void setHealth(double newHealth);

    void setInHangar();

    void restoreAirplaneHealth();

    [[nodiscard]] virtual AirplaneType getAirplaneType() const = 0;

    [[nodiscard]] virtual size_t getAirplaneCapacity() const = 0;

    [[nodiscard]] virtual bool canLand(const Runway &runway) const = 0;

    [[nodiscard]] virtual double airportFee(double ticketRevenue) const = 0;

    virtual void completeFlight() = 0;

    [[nodiscard]] virtual std::unique_ptr<Airplane> clone() const = 0;

    virtual void accept(AirplaneVisitor &visitor) = 0;
};
