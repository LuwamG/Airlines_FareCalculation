#include <iostream>
#include <vector>
#include <string>
#include "Airlines_FareCalculation.hpp"

using namespace std;

int main() {
    // Define available flights
    vector<Flight> flights = {
        {"AA101", "New York", "Los Angeles", 300.00, 2500, FareClass::Economy, false},
        {"BA202", "London", "Paris", 150.00, 500, FareClass::Business, true},
        {"CA303", "Tokyo", "Beijing", 200.00, 1000, FareClass::FirstClass, false}
    };

    // Initialize remaining seats and total seats for each flight
    short remainingSeats[] = { 50, 100, 150 };  
    short totalSeats[] = { 200, 200, 200 };    

    // Fixed baggage fee and extra baggage details
    const double baggageFee = 50.0;          
    const double extraBaggageFeePerKg = 25.0;
    const double baggageLimit = 20.0;         

    // Loop for user interaction
    do {
       
        cout << "Available Flights: \n";
        for (size_t i = 0; i < flights.size(); ++i) {
            cout << i + 1 << ". Flight Number: " << flights[i].flightNumber
                << ", From: " << flights[i].origin
                << " to " << flights[i].destination
                << ", Base Fare: $" << flights[i].baseFare << endl;
        }

        //  choose a flight
        int flightChoice;
        cout << "Select a flight by entering the number (1-3): ";
        cin >> flightChoice;

        if (flightChoice < 1 || flightChoice > 3) {
            cout << "Invalid choice. Exiting...\n";
            return 1;
        }

        // Get the selected flight and corresponding seats
        Flight selectedFlight = flights[flightChoice - 1];
        short rem = remainingSeats[flightChoice - 1];
        short tot = totalSeats[flightChoice - 1];

        // Ask for the full name of the passenger
        string fullName;
        cin.ignore();  
        cout << "Enter your full name: ";
        getline(cin, fullName);  

        // Ask the user to choose a fare class
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

        // Ask for the booking time (ensure it is in the format YYYY-MM-DD)
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

        // Ask for baggage weight
        double baggageWeight;
        cout << "Enter your baggage weight (kg): ";
        cin >> baggageWeight;

        // Calculate the fare
        double finalFare = calculateFare(selectedFlight, fareClass, bookingTime, baggageFee, rem, tot, baggageWeight, extraBaggageFeePerKg, baggageLimit);

        // Create the passenger object
        Passenger passenger = { fullName, selectedFlight.flightNumber, finalFare, baggageFee, bookingTime };

        // Display passenger details
        displayPassengerDetails(passenger, selectedFlight, baggageWeight, baggageFee);

        // Ask if the user wants to book another flight
        cout << "\nDo you want to book another flight? (y/n): ";
        char again;
        cin >> again;
        if (again != 'y' && again != 'Y') break;

    } while (true);

    return 0;
}
