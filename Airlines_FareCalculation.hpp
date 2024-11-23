#ifndef AIRLINES_FARE_CALCULATION_HPP
#define AIRLINES_FARE_CALCULATION_HPP

#include <string>
#include <vector>

using namespace std;

enum class FareClass { Economy, Business, FirstClass };

// Flight details struct
struct Flight {
    string flightNumber;
    string origin;
    string destination;
    double baseFare;
    double distance;
    FareClass fareClass;
    bool isPeakSeason;
};

// Passenger details struct
struct Passenger {
    string firstName;
    string lastName;
    string flightNumber;
    double fare;
    double baggageFee;
    string bookingTime;
    FareClass fareClass;
    double baggageWeight;
};

// Function declarations
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageFee, short remainingSeats, short totalSeats,
    double baggageWeight, double extraBaggageFeePerKg, double baggageLimit);

void addBookingToHistory(vector<Passenger>& flightHistory, const Passenger& passenger);
void displayPassengerDetails(const Passenger& passenger, const Flight& flight,
    double baggageWeight, double baggageFee);
void displayFlightHistory(const vector<Passenger>& flightHistory);
bool isValidDate(const string& date);

// Functions for input validation and username handling
int getValidIntegerInput(const string& prompt);
double getValidDoubleInput(const string& prompt);
void getValidUsername(string* firstName, string* lastName);
string getValidDateInput();

// Function to calculate the baggage fee based on the weight
double calculateBaggageFee(double baggageWeight, double baggageLimit, double extraBaggageFeePerKg);

#endif
