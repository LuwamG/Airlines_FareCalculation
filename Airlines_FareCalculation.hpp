#ifndef AIRLINES_FARECALCULATION_HPP
#define AIRLINES_FARECALCULATION_HPP

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

enum class FareClass { Economy, Business, FirstClass };

struct Flight {
    string flightNumber;
    string origin, destination;
    double baseFare;
    double distance; 
    FareClass fareClass;
    bool isPeakSeason;
};

struct Passenger {
    string fullName;
    string flightNumber;
    double fare;
    double baggageFee;
    string bookingTime;
    FareClass fareClass;
    double baggageWeight;
};

double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    const double baggageFee, short remainingSeats, short totalSeats,
    double baggageWeight, const double extraBaggageFeePerKg, const double baggageLimit);

bool isValidDate(const string& dateStr);
void addBookingToHistory(vector<Passenger>& flightHistory, const Passenger& passenger);
void displayPassengerDetails(const Passenger& passenger, const Flight& flight, double baggageWeight, double baggageFee);
void displayFlightHistory(const vector<Passenger>& flightHistory);
void saveFlightData(const string& filename, const vector<Flight>& flights);
void loadFlightData(const string& filename, vector<Flight>& flights);

#endif
