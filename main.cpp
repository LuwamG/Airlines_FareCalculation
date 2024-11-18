#include <iostream>
#include <vector>
#include <string>
#include "Airlines_FareCalculation.hpp"

using namespace std;

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
    char viewHistory;  // Reuse this variable

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
        int flightChoice;
        cout << "Select a flight by entering the number (1-3): ";
        cin >> flightChoice;

        if (flightChoice < 1 || flightChoice > 3) {
            cout << "Invalid choice. Exiting...\n";
            return 1;
        }

        Flight selectedFlight = flights[flightChoice - 1];
        short rem = remainingSeats[flightChoice - 1];
        short tot = totalSeats[flightChoice - 1];

        // Get user's full name
        string fullName;
        cin.ignore();
        cout << "Enter your full name: ";
        getline(cin, fullName);

        // Get user's fare class choice
        cout << "Choose a fare class (1 - Economy, 2 - Business, 3 - First Class): ";
        int fareChoice;
        cin >> fareChoice;
        FareClass fareClass;

        switch (fareChoice) {
        case 1:
            fareClass = FareClass::Economy;
            break;
        case 2:
            fareClass = FareClass::Business;
            break;
        case 3:
            fareClass = FareClass::FirstClass;
            break;
        default:
            cout << "Invalid choice. Exiting...\n";
            return 1;
        }

        cout << "Enter booking time (yyyy-mm-dd): ";
        string bookingTime;
        cin >> bookingTime;

        // Validate date format
        if (!isValidDate(bookingTime)) {
            cout << "Invalid date format. Exiting...\n";
            return 1;
        }

        // Get baggage weight
        double baggageWeight;
        cout << "Enter baggage weight (kg): ";
        cin >> baggageWeight;

        // Calculate the fare
        double totalFare = calculateFare(selectedFlight, fareClass, bookingTime, baggageFee, rem, tot, baggageWeight, extraBaggageFeePerKg, baggageLimit);

        // Create passenger object with fare class
        Passenger newPassenger = { fullName, selectedFlight.flightNumber, totalFare, baggageFee, bookingTime, fareClass, baggageWeight };

        // Add to history
        addBookingToHistory(flightHistory, newPassenger);

        // Display passenger details
        displayPassengerDetails(newPassenger, selectedFlight, baggageWeight, baggageFee);

        // Ask if the user wants to view previous booking history
        cout << "Would you like to view your booking history? (y/n): ";
        cin >> viewHistory;

        if (viewHistory == 'y' || viewHistory == 'Y') {
            displayFlightHistory(flightHistory);
        }

        // Ask if they want to make another booking
        cout << "Do you want to make another booking? (y/n): ";
        cin >> viewHistory;

    } while (viewHistory == 'y' || viewHistory == 'Y');

    return 0;
}
