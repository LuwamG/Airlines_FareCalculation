#include "Airlines_FareCalculation.hpp" 
#include <iostream>
#include <sstream>
#include <iomanip> 

using namespace std;

// Function to calculate the total fare based on multiple factors (fare class, baggage, demand, etc.)
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageFee, short remainingSeats, short totalSeats,
    double baggageWeight, double extraBaggageFeePerKg, double baggageLimit) {

    double totalFare = flight.baseFare; // the base fare

    // Adjust fare based on the selected fare class
    switch (fareClass) {
    case FareClass::Economy:
        totalFare *= 1.0;  // No surcharge for Economy class
        break;
    case FareClass::Business:
        totalFare *= 1.5;  // Business class is 1.5x the base fare
        break;
    case FareClass::FirstClass:
        totalFare *= 2.0;  // First class is 2x the base fare
        break;
    }

    // Apply surcharge for extra baggage if it exceeds the limit
    if (baggageWeight > baggageLimit) {
        totalFare += (baggageWeight - baggageLimit) * extraBaggageFeePerKg;
    }

    // Demand-based pricing (higher fare when fewer seats are available)
    double demandFactor = 1 + ((double)(totalSeats - remainingSeats) / totalSeats);
    totalFare *= demandFactor;

    return totalFare + baggageFee;  // Include any baggage fee in the total fare
}

// Function to validate the booking date format (yyyy-mm-dd)
bool isValidDate(const string& date) {
    // Ensure the string has the correct length and format (yyyy-mm-dd)
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;

    // Use stringstream to extract year, month, and day
    stringstream stream(date);
    int year, month, day;
    char dash1, dash2;
    if (!(stream >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-') return false;

    // Validate the year, month, and day ranges
    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) return false;

    // Check for February (leap year handling)
    if (month == 2 && (day > 29 || (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))))) return false;

    // Check for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

    return true;
}

// Function to add a booking to the flight history
void addBookingToHistory(vector<Passenger>& flightHistory, const Passenger& passenger) {
    flightHistory.push_back(passenger); // Add passenger to history
}

// Function to display passenger booking details
void displayPassengerDetails(const Passenger& passenger, const Flight& selectedFlight,
    double baggageWeight, double baggageFee) {
    cout << "\nBooking Summary: \n";
    cout << "Passenger: " << passenger.name << "\n";
    cout << "Flight Number: " << selectedFlight.flightNumber << "\n";
    cout << "Fare Class: ";

    // Display fare class as string
    switch (passenger.fareClass) {
    case FareClass::Economy: cout << "Economy"; break;
    case FareClass::Business: cout << "Business"; break;
    case FareClass::FirstClass: cout << "First Class"; break;
    }

    cout << "\nTotal Fare: $" << fixed << setprecision(2) << passenger.fare << "\n";
    cout << "Baggage Weight: " << baggageWeight << " kg\n";
    cout << "Baggage Fee: $" << baggageFee << "\n";
}

// Function to display the flight booking history for the user
void displayFlightHistory(const vector<Passenger>& flightHistory) {
    if (flightHistory.empty()) {
        cout << "No previous bookings found.\n";  // No booking history
    }
    else {
        cout << "\nBooking History:\n";
        for (const auto& passenger : flightHistory) {
            cout << "Passenger: " << passenger.name << ", Flight: " << passenger.flightNumber
                << ", Fare: $" << fixed << setprecision(2) << passenger.fare
                << ", Booking Time: " << passenger.bookingTime << endl;
        }
    }
}
