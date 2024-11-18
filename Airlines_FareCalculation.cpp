#include "Airlines_FareCalculation.hpp"
#include <iostream>
#include <cctype>  

using namespace std;

// Function to validate date format (YYYY-MM-DD)
bool isValidDate(const string& date) {
    if (date.length() != 10) {
        return false;
    }
    if (date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (i != 4 && i != 7 && !isdigit(date[i])) {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < 1000 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    return true;
}

// Fare calculation logic
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageFee, short remainingSeats, short totalSeats,
    double baggageWeight, double extraBaggageFeePerKg, double baggageLimit) {
    double finalFare = flight.baseFare;

    // Apply extra baggage fee if necessary
    if (baggageWeight > baggageLimit) {
        double extraWeight = baggageWeight - baggageLimit;
        finalFare += extraWeight * extraBaggageFeePerKg;
    }

    // Apply peak season surcharge
    if (flight.isPeakSeason) {
        finalFare *= 1.2;  // Assuming a 20% surcharge for peak season
    }

    return finalFare;
}

// Display passenger details
void displayPassengerDetails(const Passenger& passenger, const Flight& flight,
    double baggageWeight, double baggageFee) {
    cout << "\n--- Passenger Fare Summary ---\n";
    cout << "Passenger: " << passenger.name << endl;
    cout << "Flight Number: " << flight.flightNumber << endl;
    cout << "From: " << flight.origin << " to " << flight.destination << endl;
    cout << "Fare Class: " << (int)flight.fareClass << endl; 
    cout << "Booking Time: " << passenger.bookingTime << endl;
    cout << "Baggage Weight: " << baggageWeight << " kg\n";
    cout << "Baggage Fee: $" << baggageFee << endl;
    cout << "Total Fare: $" << passenger.fare << endl;
}
