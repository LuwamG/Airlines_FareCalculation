#include <iostream>
#include <vector>
#include <string>
#include "Airlines_FareCalculation.hpp"

using namespace std;

int main() {
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

    do {
        cout << "Available Flights: \n";
        for (size_t i = 0; i < flights.size(); ++i) {
            cout << i + 1 << ". Flight Number: " << flights[i].flightNumber
                << ", From: " << flights[i].origin
                << " to " << flights[i].destination
                << ", Base Fare: $" << flights[i].baseFare << endl;
        }

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

        string fullName;
        cin.ignore();
        cout << "Enter your full name: ";
        getline(cin, fullName);

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

        cout << "You have selected: " << fareClassToString(fareClass) << " class." << endl;

        string bookingTime;
        cout << "Enter the booking time (YYYY-MM-DD): ";
        while (true) {
            cin >> bookingTime;
            if (isValidDate(bookingTime)) {
                break;
            }
            else {
                cout << "Invalid date format. Please enter in the format YYYY-MM-DD: ";
            }
        }

        double baggageWeight;
        cout << "Enter your baggage weight (kg): ";
        cin >> baggageWeight;

        double finalFare = calculateFare(selectedFlight, fareClass, bookingTime, baggageFee, rem, tot, baggageWeight, extraBaggageFeePerKg, baggageLimit);

        Passenger passenger = { fullName, selectedFlight.flightNumber, finalFare, baggageFee, bookingTime };

        addBookingToHistory(flightHistory, passenger);

        displayPassengerDetails(passenger, selectedFlight, baggageWeight, baggageFee);

        cout << "\nDo you want to book another flight? (y/n): ";
        char again;
        cin >> again;
        if (again != 'y' && again != 'Y') break;

        displayFlightHistory(flightHistory);

    } while (true);

    return 0;
}
