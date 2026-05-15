cmake_minimum_required(VERSION 4.2)
project(aeroport)

set(CMAKE_CXX_STANDARD 26)

add_executable(aeroport src/main.cpp
        src/users/User.cpp
        src/users/User.h
        src/tickets/Ticket.cpp
        src/tickets/Ticket.h
        src/tickets/StandardTicket.cpp
        src/tickets/StandardTicket.h
        src/tickets/LastMinuteTicket.cpp
        src/tickets/LastMinuteTicket.h
        src/tickets/VIPTicket.cpp
        src/tickets/VIPTicket.h
        src/users/Passenger.cpp
        src/users/Passenger.h
        src/users/TrafficControl.cpp
        src/users/TrafficControl.h
        src/users/AirportAuthority.cpp
        src/users/AirportAuthority.h
        src/airplanes/Airplane.cpp
        src/airplanes/Airplane.h
        src/airplanes/PassengerPlane.cpp
        src/airplanes/PassengerPlane.h
        src/airplanes/CargoPlane.cpp
        src/airplanes/CargoPlane.h
        src/airplanes/PrivateJet.cpp
        src/airplanes/PrivateJet.h
        src/users/UserRole.cpp
        src/users/UserRole.h
        src/tickets/TicketType.cpp
        src/tickets/TicketType.h
        src/core/Airport.cpp
        src/core/Airport.h
        src/operations/Airline.cpp
        src/operations/Airline.h
        src/operations/Flight.cpp
        src/operations/Flight.h
        src/infrastructures/Runway.cpp
        src/infrastructures/Runway.h
        src/operations/flightStatus.cpp
        src/operations/flightStatus.h
        src/infrastructures/RunwayStatus.cpp
        src/infrastructures/RunwayStatus.h
        src/infrastructures/Hangar.cpp
        src/infrastructures/Hangar.h
        src/airplanes/AirplaneType.cpp
        src/airplanes/AirplaneType.h
)

target_include_directories(aeroport PRIVATE src)
