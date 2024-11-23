#include "Airlines_FareCalculation.hpp"
#include <iostream>
#include <sstream>
#include <cctype>

using namespace std;

// Function to validate a date (simple check for format, and valid month/day)
bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    // Check if all characters are digits where expected
    for (int i = 0; i < 10; ++i) {
        if (i != 4 && i != 7 && !isdigit(date[i])) {
            return false;
        }
    }

    // Further checks on date (e.g., valid month and day ranges)
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    // Simple validation: months should be 1-12, days 1-31
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
    return true;
}

//  function to get a valid username (first and last name)
void getValidUsername(string& firstName, string& lastName) {
    while (true) {
        cout << "Enter full name (First Last): ";
        string fullName;
        getline(cin, fullName);  

        // Use stringstream to parse the full name into first and last names
        stringstream nameStream(fullName);
        if (!(getline(nameStream, firstName, ' ') && getline(nameStream, lastName))) {
            cout << "Invalid input. Please enter both first and last names.\n";
        }
        else if (firstName.empty() || lastName.empty()) {
            cout << "Invalid input. Both first and last names must be non-empty.\n";
        }
        else {
          
            firstName.erase(0, firstName.find_first_not_of(' '));
            lastName.erase(0, lastName.find_first_not_of(' '));
            break;  
        }
    }
}


string getValidDateInput() {
    string date;
    while (true) {
        cout << "Enter booking date (yyyy-mm-dd): ";
        cin >> date;
        if (isValidDate(date)) {
            return date;
        }
        else {
            cout << "Invalid date format. Please enter the date as yyyy-mm-dd and make sure the date is valid.\n";
        }
    }
}

// Improved integer input validation
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

// Improved double input validation (ensuring baggage weight is positive)
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
// Function to calculate the total fare based on flight and class
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageWeight, double baggageFee) {
    double totalFare = flight.baseFare;

    switch (fareClass) {
    case FareClass::Economy:
        totalFare += flight.baseFare * 0.1; // Add 10% for Economy
        break;
    case FareClass::Business:
        totalFare += flight.baseFare * 0.2; // Add 20% for Business
        break;
    case FareClass::FirstClass:
        totalFare += flight.baseFare * 0.3; // Add 30% for First Class
        break;
    }

    totalFare += baggageFee; // Add baggage fee
    return totalFare;
}
// Function to calculate additional baggage fees if weight exceeds the limit
double calculateBaggageFee(double baggageWeight, double baggageLimit, double extraBaggageFeePerKg) {
    if (baggageWeight > baggageLimit) {
        return (baggageWeight - baggageLimit) * extraBaggageFeePerKg;
    }
    return 0.0;
}
// Add the current passenger booking to history
void addBookingToHistory(shared_ptr<Passenger> flightHistory[], int& passengerCount, shared_ptr<Passenger> passenger) {
    flightHistory[passengerCount] = passenger;
    ++passengerCount;
}
// Display details of a passenger's booking
void displayPassengerDetails(const shared_ptr<Passenger>& passenger, const Flight& selectedFlight) {
    cout << "\nBooking Summary:\n";
    cout << "Passenger: " << passenger->firstName << " " << passenger->lastName << "\n";
    cout << "Flight Number: " << selectedFlight.flightNumber << "\n";
    cout << "Total Fare: $" << fixed << setprecision(2) << passenger->totalFare << "\n";
    cout << "Baggage Fee: $" << fixed << setprecision(2) << passenger->baggageFee << "\n";
    cout << "Booking Time: " << passenger->bookingTime << "\n";
}
// Display all flight history for the user
void displayFlightHistory(shared_ptr<Passenger> flightHistory[], int passengerCount) {
    cout << "\nBooking History:\n";
    for (int i = 0; i < passengerCount; ++i) {
        displayPassengerDetails(flightHistory[i], { flightHistory[i]->flightNumber, "", "", 0, 0, {}, false });
    }
}
