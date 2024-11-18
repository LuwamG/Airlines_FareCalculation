#ifndef AIRLINES_FARECALCULATION_HPP
#define AIRLINES_FARECALCULATION_HPP

#include <string>
#include <vector>

using namespace std;

enum class FareClass {
    Economy = 1,
    Business,
    FirstClass
};

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

double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageFee, short remainingSeats, short totalSeats, double baggageWeight,
    double extraBaggageFeePerKg, double baggageLimit);

bool isValidDate(const string& date);

void displayPassengerDetails(const Passenger& passenger, const Flight& flight, double baggageWeight, double baggageFee);

void displayFlightHistory(const vector<Passenger>& history);

void addBookingToHistory(vector<Passenger>& history, const Passenger& passenger);

string fareClassToString(FareClass fareClass);

#endif 
