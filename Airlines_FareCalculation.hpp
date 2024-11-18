#ifndef AIRLINES_FARECALCULATION_HPP
#define AIRLINES_FARECALCULATION_HPP

#include <string>
#include <vector>
#include <memory>  // For smart pointers

using namespace std;

// Enumeration for fare classes
enum class FareClass {
    Economy,
    Business,
    FirstClass
};

// Enumeration for peak season
enum class Season {
    Peak,
    OffPeak
};

// Structure to hold flight information
struct Flight {
    string flightNumber;
    string origin;
    string destination;
    double baseFare;
    double distance;
    FareClass fareClass;
    Season season;  // Whether it's peak season or off-peak
};

// Structure to hold passenger information
struct Passenger {
    string name;
    string flightNumber;
    double fare;
    double baggageFee;
    string bookingTime;
};

// Function to calculate the fare based on various factors
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime);

// Function to adjust price based on remaining seats and demand
double adjustPriceBasedOnDemand(double baseFare, int remainingSeats, int totalSeats);

// Function to apply seasonality surcharge based on whether it's peak season
double applySeasonalitySurcharge(double baseFare, Season season);

// Functions to load and save flight data to/from a file
void saveFlightData(const string& filename, unique_ptr<Flight[]>& flights, int size);
void loadFlightData(const string& filename, unique_ptr<Flight[]>& flights, int& size);

#endif
