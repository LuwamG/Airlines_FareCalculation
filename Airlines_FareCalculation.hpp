#ifndef AIRLINES_FARECALCULATION_HPP
#define AIRLINES_FARECALCULATION_HPP

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

enum class FareClass { Economy, Business, FirstClass };

struct Flight {
    string flightNumber;
    string origin;
    string destination;
    double baseFare;
    double distance;
    FareClass fareClass;
    bool isPeakSeason;
};

struct Passenger {
    string name;
    string flightNumber;
    double fare;
    double baggageFee;
    string bookingTime;
};

double adjustFareBasedOnDistance(double fare, double distance);
double adjustPriceBasedOnDemand(double fare, int remainingSeats, int totalSeats);
double applySeasonalitySurcharge(double fare, bool isPeakSeason);
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime, double baggageFee);
void displayFlightDetails(const Flight& flight);
void displayPassengerDetails(const Passenger& passenger, const Flight& flight, double baggageFee);

#endif
