#include <iostream>
#include <string>
#include <limits>
#include <memory>
#include <iomanip>
#include "Airlines_FareCalculation.hpp"

using namespace std;

int main() {
    // Define max number of passengers
    const int maxPassengers = 10;  // For example, 10 passengers
    shared_ptr<Passenger> flightHistory[maxPassengers];  // Use array of shared_ptr to manage Passenger objects
    int passengerCount = 0;

    // Available flights (example data)
    Flight flights[3] = {
        {"FL001", "New York", "London", 500.00, 3000.0, FareClass::Economy, false},
        {"FL002", "Chicago", "Paris", 600.00, 4500.0, FareClass::Business, true},
        {"FL003", "Los Angeles", "Tokyo", 800.00, 6000.0, FareClass::FirstClass, false}
    };

    char bookAnotherFlight = 'Y';
    char viewHistory = 'N';

    do {
        // Show available flights
        cout << "Available Flights:\n";
        for (size_t i = 0; i < 3; i++) {
            cout << i + 1 << ". Flight Number: " << flights[i].flightNumber
                << ", From: " << flights[i].origin << " to " << flights[i].destination
                << ", Base Fare: $" << fixed << setprecision(2) << flights[i].baseFare << "\n";
        }

        int flightChoice = getValidIntegerInput("Select a flight by entering the number (1-3): ");
        cin.ignore();  // Clear the buffer before taking the passenger name input

        string firstName, lastName;
        getValidUsername(firstName, lastName); // Get full name using parsing

        FareClass fareClass = static_cast<FareClass>(getValidIntegerInput("Enter Fare Class (1: Economy, 2: Business, 3: First Class): ") - 1);
        double baggageWeight = getValidDoubleInput("Enter baggage weight (in kg): ");
        string bookingTime = getValidDateInput();  // Get valid booking date

        Flight selectedFlight = flights[flightChoice - 1];
        double baggageFee = calculateBaggageFee(baggageWeight, 20.0, 10.0);
        double totalFare = calculateFare(selectedFlight, fareClass, bookingTime, baggageWeight, baggageFee);

        // Create and store passenger booking
        shared_ptr<Passenger> passenger = make_shared<Passenger>(firstName, lastName, selectedFlight.flightNumber, totalFare, baggageFee, bookingTime, fareClass, baggageWeight);
        addBookingToHistory(flightHistory, passengerCount, passenger);

        // Show the booking summary
        displayPassengerDetails(passenger, selectedFlight);

        cout << "Do you want to book another flight? (Y/N): ";
        cin >> bookAnotherFlight;
    } while (bookAnotherFlight == 'Y' || bookAnotherFlight == 'y');

    // Ask if the user wants to view booking history
    cout << "\nDo you want to view your booking history? (Y/N): ";
    cin >> viewHistory;
    if (viewHistory == 'Y' || viewHistory == 'y') {
        displayFlightHistory(flightHistory, passengerCount);
    }

    return 0;
}
