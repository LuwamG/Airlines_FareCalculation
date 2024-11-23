#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
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
    const double extraBaggageFeePerKg = 10.0;
    const double baggageLimit = 20.0;

    vector<Passenger> flightHistory;
    char bookAnotherFlight = 'Y';
    char viewHistory = 'N';

    do {
        // Show available flights
        cout << "Available Flights:\n";
        for (size_t i = 0; i < flights.size(); i++) {
            cout << i + 1 << ". Flight Number: " << flights[i].flightNumber
                << ", From: " << flights[i].origin << " to " << flights[i].destination
                << ", Base Fare: $" << fixed << setprecision(2) << flights[i].baseFare << "\n";
        }

        int flightChoice = getValidIntegerInput("Select a flight by entering the number (1-3): ");
        cin.ignore();  // Clear the buffer before taking the passenger name input

        string firstName, lastName;
        getValidUsername(&firstName, &lastName); // Get full name using pointer

        FareClass fareClass = static_cast<FareClass>(getValidIntegerInput("Enter Fare Class (1: Economy, 2: Business, 3: First Class): ") - 1);
        double baggageWeight = getValidDoubleInput("Enter baggage weight (in kg): ");
        string bookingTime = getValidDateInput();  // Get valid booking date

        Flight selectedFlight = flights[flightChoice - 1];
        double totalFare = calculateFare(selectedFlight, fareClass, bookingTime, baggageFee,
            remainingSeats[flightChoice - 1], totalSeats[flightChoice - 1], baggageWeight,
            extraBaggageFeePerKg, baggageLimit);

        // Create and store passenger booking
        Passenger passenger = { firstName, lastName, selectedFlight.flightNumber, totalFare, baggageFee, bookingTime, fareClass, baggageWeight };
        addBookingToHistory(flightHistory, passenger);

        // Show the booking summary
        displayPassengerDetails(passenger, selectedFlight, baggageWeight, baggageFee);

        cout << "\nDo you want to book another flight? (Y/N): ";
        cin >> bookAnotherFlight;
    } while (bookAnotherFlight == 'Y' || bookAnotherFlight == 'y');

    // Ask if the user wants to view booking history
    cout << "\nDo you want to view your booking history? (Y/N): ";
    cin >> viewHistory;
    if (viewHistory == 'Y' || viewHistory == 'y') {
        displayFlightHistory(flightHistory);
    }

    return 0;
}
