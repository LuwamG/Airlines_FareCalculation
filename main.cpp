#include <iostream>
#include <string>
#include <limits>
#include <memory>  
#include <iomanip>  
#include "Airlines_FareCalculation.hpp"  

using namespace std;

int main() {
    // Define maximum number of passengers to be stored in the flight history
    const int maxPassengers = 10; 
    shared_ptr<Passenger> flightHistory[maxPassengers];  // Array of shared_ptr to hold Passenger objects
    int passengerCount = 0;  // Counter to track the number of passengers in history

    // Available flights (example data for flights)
    Flight flights[3] = {
        {"FL001", "New York", "London", 500.00, 3000.0, FareClass::Economy, false},  
        {"FL002", "Chicago", "Paris", 600.00, 4500.0, FareClass::Business, true},    
        {"FL003", "Los Angeles", "Tokyo", 800.00, 6000.0, FareClass::FirstClass, false} 
    };

    char bookAnotherFlight = 'Y';  // Variable to ask user if they want to book another flight
    char viewHistory = 'N';  // Variable to check if user wants to view booking history

    do {
        // Display the list of available flights for booking
        cout << "Available Flights:\n";
        for (size_t i = 0; i < 3; i++) {  // Loop through the available flights and display details
            cout << i + 1 << ". Flight Number: " << flights[i].flightNumber
                << ", From: " << flights[i].origin << " to " << flights[i].destination
                << ", Base Fare: $" << fixed << setprecision(2) << flights[i].baseFare << "\n";
        }

        // Prompt user to select a flight (1-3)
        int flightChoice = getValidIntegerInput("Select a flight by entering the number (1-3): ");
        cin.ignore();  // Clear the input buffer before taking passenger name input

        string firstName, lastName;  // Variables to store passenger's first and last name
        getValidUsername(firstName, lastName); // Get the full name by calling a helper function to parse the name

        // Ask user to select the fare class (Economy, Business, or First Class)
        FareClass fareClass = static_cast<FareClass>(getValidIntegerInput("Enter Fare Class (1: Economy, 2: Business, 3: First Class): ") - 1);

        // Get the weight of the passenger's baggage
        double baggageWeight = getValidDoubleInput("Enter baggage weight (in kg): ");

        // Get the booking date using the helper function
        string bookingTime = getValidDateInput();  

        // Retrieve the selected flight's details from the flights array
        Flight selectedFlight = flights[flightChoice - 1];

        // Calculate the baggage fee based on weight and limit (example limit: 20 kg and extra fee: $10 per kg)
        double baggageFee = calculateBaggageFee(baggageWeight, 20.0, 10.0);

        // Calculate the total fare for the booking using the selected flight and fare class
        double totalFare = calculateFare(selectedFlight, fareClass, bookingTime, baggageWeight, baggageFee);

        // Create a new Passenger object and store the booking details using smart pointers
        shared_ptr<Passenger> passenger = make_shared<Passenger>(firstName, lastName, selectedFlight.flightNumber, totalFare, baggageFee, bookingTime, fareClass, baggageWeight);

        // Add the passenger's booking to the flight history
        addBookingToHistory(flightHistory, passengerCount, passenger);

        // Display the booking details (summary) to the user
        displayPassengerDetails(passenger, selectedFlight);

        // Ask the user if they want to book another flight
        cout << "Do you want to book another flight? (Y/N): ";
        cin >> bookAnotherFlight;
    } while (bookAnotherFlight == 'Y' || bookAnotherFlight == 'y'); 

    // Ask the user if they want to view their booking history
    cout << "\nDo you want to view your booking history? (Y/N): ";
    cin >> viewHistory;

    // If the user wants to view history, display all previous bookings
    if (viewHistory == 'Y' || viewHistory == 'y') {
        displayFlightHistory(flightHistory, passengerCount);
    }

    return 0;  
}
