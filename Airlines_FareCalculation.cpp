#include "Airlines_FareCalculation.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>

// Function to calculate fare based on flight details, booking time, and baggage
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime, double baggageFee, short remainingSeats, short totalSeats, double baggageWeight, double extraBaggageFeePerKg, double baggageLimit) {
    double finalFare = flight.baseFare;

    // Adjust price based on demand (remaining seats)
    finalFare += (totalSeats - remainingSeats) * 0.1 * finalFare; // Increase fare with fewer remaining seats

    // Add seasonality surcharge if peak season
    if (flight.isPeakSeason) {
        finalFare *= 1.2; // Increase fare by 20% in peak season
    }

    // Add extra baggage fee if baggage exceeds limit
    if (baggageWeight > baggageLimit) {
        finalFare += (baggageWeight - baggageLimit) * extraBaggageFeePerKg;
    }

    // Adjust fare based on selected fare class
    switch (fareClass) {
    case FareClass::Economy:
        finalFare += 0;  // No additional charge for economy
        break;
    case FareClass::Business:
        finalFare += 100;  // Add $100 for business class
        break;
    case FareClass::FirstClass:
        finalFare += 200;  // Add $200 for first class
        break;
    }

    // Add baggage fee
    finalFare += baggageFee;

    return finalFare;
}

// Convert fare class enum to string
string fareClassToString(FareClass fareClass) {
    switch (fareClass) {
    case FareClass::Economy: return "Economy";
    case FareClass::Business: return "Business";
    case FareClass::FirstClass: return "First Class";
    default: return "Unknown";
    }
}

// Validate the date format (YYYY-MM-DD)
bool isValidDate(const string& date) {
    if (date.length() != 10) return false;
    for (int i = 0; i < 10; ++i) {
        if ((i == 4 || i == 7) && date[i] != '-') return false;
        if (i != 4 && i != 7 && !isdigit(date[i])) return false;
    }
    return true;
}

// Add booking to history
void addBookingToHistory(vector<Passenger>& flightHistory, const Passenger& passenger) {
    flightHistory.push_back(passenger);
}

// Display passenger details
void displayPassengerDetails(const Passenger& passenger, const Flight& selectedFlight, double baggageWeight, double baggageFee) {
    cout << "\n--- Passenger Fare Summary ---\n";
    cout << "Passenger: " << passenger.name << "\n";
    cout << "Flight Number: " << selectedFlight.flightNumber << "\n";
    cout << "From: " << selectedFlight.origin << " to " << selectedFlight.destination << "\n";
    cout << "Fare Class: " << fareClassToString(selectedFlight.fareClass) << "\n";
    cout << "Booking Time: " << passenger.bookingTime << "\n";
    cout << "Baggage Weight: " << baggageWeight << " kg\n";
    cout << "Baggage Fee: $" << baggageFee << "\n";
    cout << "Total Fare: $" << passenger.fare << "\n";
    cout << "-----------------------------\n";
}

// Display flight history (show all previous bookings)
void displayFlightHistory(const vector<Passenger>& history) {
    if (history.empty()) {
        cout << "\nNo previous bookings found.\n";  // If no history, inform the user
    }
    else {
        cout << "\n--- Flight Booking History ---\n";
        for (const auto& passenger : history) {
            cout << "Name: " << passenger.name << "\n";
            cout << "Flight Number: " << passenger.flightNumber << "\n";
            cout << "Fare Class: " << fareClassToString((FareClass)passenger.fare) << "\n";
            cout << "Booking Time: " << passenger.bookingTime << "\n";
            cout << "Baggage Fee: $" << passenger.baggageFee << "\n";
            cout << "Total Fare: $" << passenger.fare << "\n";
            cout << "-----------------------------\n";
        }
    }
}
