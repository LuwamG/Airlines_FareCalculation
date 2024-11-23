#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "Airlines_FareCalculation.hpp"

using namespace std;

// Function to calculate baggage fee based on weight
double calculateBaggageFee(double baggageWeight, double baggageLimit, double extraBaggageFeePerKg) {
    if (baggageWeight > baggageLimit) {
        // Calculate excess baggage fee
        double excessWeight = baggageWeight - baggageLimit;
        return excessWeight * extraBaggageFeePerKg;
    }
    return 0.0; // No baggage fee if within the limit
}

// Function to calculate the total fare based on different factors
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageFee, short remainingSeats, short totalSeats,
    double baggageWeight, double extraBaggageFeePerKg, double baggageLimit) {

    double totalFare = flight.baseFare;

    // Adjust fare for the class selected
    switch (fareClass) {
    case FareClass::Economy:
        totalFare *= 1.0;  // No surcharge for Economy
        break;
    case FareClass::Business:
        totalFare *= 1.5;  // Business class is 1.5x base fare
        break;
    case FareClass::FirstClass:
        totalFare *= 2.0;  // First class is 2x base fare
        break;
    }

    // Apply peak season surcharge
    if (flight.isPeakSeason) {
        totalFare *= 1.2;  // Peak season increases fare by 20%
    }

    // Apply baggage surcharge for extra baggage
    double baggageExcessFee = calculateBaggageFee(baggageWeight, baggageLimit, extraBaggageFeePerKg);
    totalFare += baggageExcessFee;

    // Demand-based pricing (higher fare when fewer seats are left)
    double demandFactor = 1 + ((double)(totalSeats - remainingSeats) / totalSeats);
    totalFare *= demandFactor;

    return totalFare + baggageFee;
}

// Function to validate the booking date format (yyyy-mm-dd)
bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;

    stringstream stream(date);
    int year, month, day;
    char dash1, dash2;
    if (!(stream >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-') return false;

    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) return false;

    if (month == 2 && (day > 29 || (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))))) return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

    return true;
}

// Function to add booking to the flight history
void addBookingToHistory(vector<Passenger>& flightHistory, const Passenger& passenger) {
    flightHistory.push_back(passenger);
}

// Function to display passenger details
void displayPassengerDetails(const Passenger& passenger, const Flight& selectedFlight,
    double baggageWeight, double baggageFee) {
    cout << "\nBooking Summary: \n";
    cout << "Passenger: " << passenger.firstName << " " << passenger.lastName << "\n";
    cout << "Flight Number: " << selectedFlight.flightNumber << "\n";
    cout << "Fare Class: ";
    switch (passenger.fareClass) {
    case FareClass::Economy: cout << "Economy"; break;
    case FareClass::Business: cout << "Business"; break;
    case FareClass::FirstClass: cout << "First Class"; break;
    }
    cout << "\nTotal Fare: $" << fixed << setprecision(2) << passenger.fare << "\n";
    cout << "Baggage Weight: " << baggageWeight << " kg\n";
    cout << "Baggage Fee: $" << baggageFee << "\n";
}

// Function to display flight history for the user
void displayFlightHistory(const vector<Passenger>& flightHistory) {
    if (flightHistory.empty()) {
        cout << "No previous bookings found.\n";
    }
    else {
        cout << "\nBooking History:\n";
        for (const auto& passenger : flightHistory) {
            cout << "Passenger: " << passenger.firstName << " " << passenger.lastName
                << ", Flight: " << passenger.flightNumber
                << ", Fare: $" << fixed << setprecision(2) << passenger.fare
                << ", Booking Time: " << passenger.bookingTime << endl;
        }
    }
}

// Function to ensure the input is a valid integer.
int getValidIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value < 1) {
                cout << "Input must be a positive integer.\n";
                continue;
            }
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

// Function to get a valid username input
void getValidUsername(string* firstName, string* lastName) {
    while (true) {
        cout << "Enter your First Name and Last Name (separated by a space): ";
        cin >> *firstName >> *lastName;

        // Ensure both first and last name are entered.
        if (!firstName->empty() && !lastName->empty()) {
            break;
        }
        else {
            cout << "Both first name and last name are required. Please try again.\n";
        }
    }
}

// Function to get a valid date input (yyyy-mm-dd)
string getValidDateInput() {
    string date;
    while (true) {
        cout << "Enter booking date (yyyy-mm-dd): ";
        getline(cin, date);
        if (isValidDate(date)) {
            return date;
        }
        else {
            cout << "Invalid date format. Please use the format yyyy-mm-dd.\n";
        }
    }
}
