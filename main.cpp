#include <iostream>
#include <vector>
#include <string>
#include "Airlines_FareCalculation.hpp"  // Include the header for function declarations

using namespace std;

// Function to ensure the input is a valid integer.
int getValidIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        }
        else {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        }
    }
}

// Function to ensure the input is a valid double.
double getValidDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            return value;
        }
        else {
            cout << "Invalid input. Please enter a valid positive number.\n";
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        }
    }
}

int main() {
    // Sample flights available
    vector<Flight> flights = {
        {"AA101", "New York", "Los Angeles", 300.00, 2500, FareClass::Economy, false},
        {"BA202", "London", "Paris", 150.00, 500, FareClass::Business, true},
        {"CA303", "Tokyo", "Beijing", 200.00, 1000, FareClass::FirstClass, false}
    };

    short remainingSeats[] = { 50, 100, 150 };
    short totalSeats[] = { 200, 200, 200 };

    const double baggageFee = 50.0;
    const double extraBaggageFeePerKg = 25.0;
    const double baggageLimit = 20.0;

    vector<Passenger> flightHistory;
    char viewHistory;

    do {
        // Show available flights
        cout << "Available Flights: \n";
        for (size_t i = 0; i < flights.size(); ++i) {
            cout << i + 1 << ". Flight Number: " << flights[i].flightNumber
                << ", From: " << flights[i].origin
                << " to " << flights[i].destination
                << ", Base Fare: $" << flights[i].baseFare << endl;
        }

        // Get user choice for flight
        int flightChoice = getValidIntegerInput("Select a flight by entering the number (1-3): ");

        if (flightChoice < 1 || flightChoice > 3) {
            cout << "Invalid flight selection. Please try again.\n";
            continue;
        }

        // Get passenger details
        string passengerName;
        cout << "Enter passenger name: ";
        cin.ignore();
        getline(cin, passengerName);

        FareClass selectedFareClass = (FareClass)getValidIntegerInput("Select Fare Class (1: Economy, 2: Business, 3: First Class): ");
        double baggageWeight = getValidDoubleInput("Enter baggage weight in kg: ");

        // Calculate the fare
        Flight selectedFlight = flights[flightChoice - 1];
        double totalFare = calculateFare(selectedFlight, selectedFareClass, "2024-11-16", baggageFee,
            remainingSeats[flightChoice - 1], totalSeats[flightChoice - 1],
            baggageWeight, extraBaggageFeePerKg, baggageLimit);

        // Store passenger info
        Passenger newPassenger = { passengerName, selectedFlight.flightNumber, totalFare, baggageFee, "2024-11-16", selectedFareClass, baggageWeight };
        addBookingToHistory(flightHistory, newPassenger);

        // Display passenger details
        displayPassengerDetails(newPassenger, selectedFlight, baggageWeight, baggageFee);

        // Option to view booking history
        cout << "Would you like to view your booking history? (Y/N): ";
        cin >> viewHistory;

    } while (viewHistory == 'Y' || viewHistory == 'y');

    return 0;
}
