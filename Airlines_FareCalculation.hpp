#ifndef AIRLINES_FARE_CALCULATION_HPP
#define AIRLINES_FARE_CALCULATION_HPP

#include <string>
#include <vector>

// Enum to represent the fare class
enum class FareClass {
    Economy,
    Business,
    FirstClass
};

// Structure for Flight details
struct Flight {
    std::string flightNumber;
    std::string origin, destination;
    double baseFare;
    double distance;
    FareClass fareClass;
    bool isPeakSeason;
};

// Structure for Passenger details
struct Passenger {
    std::string name;
    std::string flightNumber;
    double fare;
    double baggageFee;
    std::string bookingTime;
};

// Function to calculate the fare based on various parameters
double calculateFare(const Flight& flight, FareClass fareClass, const std::string& bookingTime,
    double baggageFee, short remainingSeats, short totalSeats, double baggageWeight,
    double extraBaggageFeePerKg, double baggageLimit);

// Function to display the passenger details
void displayPassengerDetails(const Passenger& passenger, const Flight& flight, double baggageWeight, double baggageFee);

// Function to save flight data to a file
void saveFlightData(const std::string& filename, const std::vector<Flight>& flights);

// Function to load flight data from a file
void loadFlightData(const std::string& filename, std::vector<Flight>& flights);

#endif 
