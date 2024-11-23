#include "Airlines_FareCalculation.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <memory>  

using namespace std;

// Function to calculate the total fare based on flight and class
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageWeight, double baggageFee) {
    double totalFare = flight.baseFare;

    // Adjust fare based on class
    if (fareClass == FareClass::Business)
        totalFare *= 1.5;  // Business class adds 50% to the base fare
    else if (fareClass == FareClass::FirstClass)
        totalFare *= 2.0;  // First Class adds 100% to the base fare

    // Add baggage fee to the total fare
    totalFare += baggageFee;

    return totalFare;
}

// Function to calculate additional baggage fees if weight exceeds the limit
double calculateBaggageFee(double baggageWeight, double baggageLimit, double extraBaggageFeePerKg) {
    if (baggageWeight > baggageLimit) {
        // If baggage weight exceeds the limit, charge extra
        return (baggageWeight - baggageLimit) * extraBaggageFeePerKg;
    }
    return 0.0;  // No extra charge if within the limit
}

// Add the current passenger booking to history
void addBookingToHistory(shared_ptr<Passenger> flightHistory[], int& passengerCount, shared_ptr<Passenger> passenger) {
    flightHistory[passengerCount] = passenger;  // Store shared_ptr to passenger
    passengerCount++;  // Increment passenger count
}

// Display details of a passenger's booking
void displayPassengerDetails(const shared_ptr<Passenger>& passenger, const Flight& selectedFlight) {
    cout << "\nBooking Summary:\n";
    cout << "Passenger: " << passenger->firstName << " " << passenger->lastName << "\n";
    cout << "Flight Number: " << selectedFlight.flightNumber << "\n";
    cout << "Fare Class: ";
    switch (passenger->fareClass) {
    case FareClass::Economy: cout << "Economy"; break;
    case FareClass::Business: cout << "Business"; break;
    case FareClass::FirstClass: cout << "First Class"; break;
    }
    cout << "\nTotal Fare: $" << fixed << setprecision(2) << passenger->totalFare << "\n";
    cout << "Baggage Weight: " << passenger->baggageWeight << " kg\n";
    cout << "Baggage Fee: $" << fixed << setprecision(2) << passenger->baggageFee << "\n";
}

// Display all flight history for the user
void displayFlightHistory(shared_ptr<Passenger> flightHistory[], int passengerCount) {
    if (passengerCount == 0) {
        cout << "No previous bookings found.\n";
    }
    else {
        cout << "\nBooking History:\n";
        for (int i = 0; i < passengerCount; ++i) {
            cout << flightHistory[i]->firstName << " " << flightHistory[i]->lastName
                << " - Flight: " << flightHistory[i]->flightNumber << ", Fare: $"
                << fixed << setprecision(2) << flightHistory[i]->totalFare << "\n";
        }
    }
}

// Get a valid integer input from the user
int getValidIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;  // Return valid integer
        }
        else {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        }
    }
}

// Get a valid double input from the user
double getValidDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= 0) {
            return value;  // Return valid positive number
        }
        else {
            cout << "Invalid input. Please enter a valid positive number.\n";
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
        }
    }
}

// Get a valid booking date input
string getValidDateInput() {
    string date;
    while (true) {
        cout << "Enter booking date (yyyy-mm-dd): ";
        cin >> date;
        if (date.size() == 10 && date[4] == '-' && date[7] == '-' && isdigit(date[0]) && isdigit(date[1]) && isdigit(date[2]) && isdigit(date[3])) {
            return date;
        }
        else {
            cout << "Invalid date format. Please enter the date as yyyy-mm-dd.\n";
        }
    }
}

// Get the full name (first and last) and validate input
void getValidUsername(string& firstName, string& lastName) {
    while (true) {
        cout << "Enter full name (First Last): ";
        string fullName;
        getline(cin, fullName);  

        stringstream nameStream(fullName);  // Create a stringstream from the full name
        getline(nameStream, firstName, ' ');  // Parse the first name
        getline(nameStream, lastName);  // Parse the last name

        // Check if both first and last names are valid
        if (!firstName.empty() && !lastName.empty()) {
            break;  
        }
        else {
            cout << "Invalid input. Please enter both first and last names.\n";
        }
    }
}
