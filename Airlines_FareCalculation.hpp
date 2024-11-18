#ifndef AIRLINES_FARE_CALCULATION_HPP
#define AIRLINES_FARE_CALCULATION_HPP

#include <iostream>
#include <vector>
#include <string>


// Enum for fare classes
enum class FareClass {
    Economy = 1,
    Business,
    FirstClass
};

// Struct to store flight details
struct Flight {
    string flightNumber;
    string origin;
    string destination;
    double baseFare;
    double distance;
    FareClass fareClass;
    bool isPeakSeason;
};

// Struct to store passenger details
struct Passenger {
    string name;
    string flightNumber;
    double fare;
    double baggageFee;
    string bookingTime;
};

// Function prototypes
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime, double baggageFee, short remainingSeats, short totalSeats, double baggageWeight, double extraBaggageFeePerKg, double baggageLimit);
string fareClassToString(FareClass fareClass);
bool isValidDate(const string& date);
void addBookingToHistory(vector<Passenger>& flightHistory, const Passenger& passenger);
void displayPassengerDetails(const Passenger& passenger, const Flight& selectedFlight, double baggageWeight, double baggageFee);
void displayFlightHistory(const vector<Passenger>& history);

#endif
