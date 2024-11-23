#ifndef AIRLINES_FARE_CALCULATION_HPP
#define AIRLINES_FARE_CALCULATION_HPP

#include <string>
#include <vector>

using namespace std;

enum class FareClass { Economy, Business, FirstClass };

// Structure to store flight details
struct Flight {
    string flightNumber;
    string origin;
    string destination;
    double baseFare;
    double distance;
    FareClass fareClass;
    bool isPeakSeason; // Indicates if it's peak season
};

// Structure to store passenger booking details
struct Passenger {
    string name;
    string flightNumber;
    double fare;
    double baggageFee;
    string bookingTime;  // Date of booking (yyyy-mm-dd format)
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
bool isValidDate(const string& date);  // Function to validate booking date format (yyyy-mm-dd)

#endif
