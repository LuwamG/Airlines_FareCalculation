#include "Airlines_FareCalculation.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageFee, short remainingSeats, short totalSeats, double baggageWeight,
    double extraBaggageFeePerKg, double baggageLimit) {
    double fare = flight.baseFare;

    if (flight.isPeakSeason) {
        fare += fare * 0.15;  // 15% surcharge
    }

    double demandFactor = 1.0;
    if (remainingSeats < totalSeats * 0.2) {
        demandFactor = 1.2; // 20% increase if fewer than 20% seats are available
    }
    fare *= demandFactor;

    if (baggageWeight > baggageLimit) {
        double excessWeight = baggageWeight - baggageLimit;
        fare += excessWeight * extraBaggageFeePerKg;
    }

    return fare + baggageFee;
}

bool isValidDate(const string& date) {
    if (date.size() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}

void displayPassengerDetails(const Passenger& passenger, const Flight& flight, double baggageWeight, double baggageFee) {
    cout << "\n--- Passenger Fare Summary ---\n";
    cout << "Passenger: " << passenger.name << endl;
    cout << "Flight Number: " << passenger.flightNumber << endl;
    cout << "From: " << flight.origin << " to " << flight.destination << endl;
    cout << "Fare Class: " << fareClassToString(flight.fareClass) << endl;
    cout << "Booking Time: " << passenger.bookingTime << endl;
    cout << "Baggage Weight: " << baggageWeight << " kg" << endl;
    cout << "Baggage Fee: $" << baggageFee << endl;
    cout << "Total Fare: $" << passenger.fare << endl;
}

void displayFlightHistory(const vector<Passenger>& history) {
    if (history.empty()) {
        cout << "\nNo previous bookings found.\n";
    }
    else {
        cout << "\n--- Flight Booking History ---\n";
        for (const auto& passenger : history) {
            cout << "Name: " << passenger.name << endl;
            cout << "Flight Number: " << passenger.flightNumber << endl;
            cout << "Fare Class: " << fareClassToString((FareClass)passenger.fare) << endl;
            cout << "Booking Time: " << passenger.bookingTime << endl;
            cout << "Baggage Fee: $" << passenger.baggageFee << endl;
            cout << "Total Fare: $" << passenger.fare << endl;
            cout << "---------------------------------\n";
        }
    }
}

void addBookingToHistory(vector<Passenger>& history, const Passenger& passenger) {
    history.push_back(passenger);
}

string fareClassToString(FareClass fareClass) {
    switch (fareClass) {
    case FareClass::Economy:   return "Economy";
    case FareClass::Business:  return "Business";
    case FareClass::FirstClass: return "First Class";
    default: return "Unknown";
    }
}
