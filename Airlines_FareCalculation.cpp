#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include "Airlines_FareCalculation.hpp"
using namespace std;

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

    // Apply baggage surcharge for extra baggage
    if (baggageWeight > baggageLimit) {
        totalFare += (baggageWeight - baggageLimit) * extraBaggageFeePerKg;
    }

    // Demand-based pricing (higher fare when fewer seats are left)
    double demandFactor = 1 + ((double)(totalSeats - remainingSeats) / totalSeats);
    totalFare *= demandFactor;

    return totalFare + baggageFee;
}

bool isValidDate(const string& date) {
    // Ensure the string has the correct length and format (yyyy-mm-dd)
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;

    // Use a stringstream to extract year, month, and day
    stringstream stream(date);
    int year, month, day;
    char dash1, dash2;
    if (!(stream >> year >> dash1 >> month >> dash2 >> day) || dash1 != '-' || dash2 != '-') return false;

    // Validate the year, month, and day ranges
    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) return false;

    // February check (leap year)
    if (month == 2 && (day > 29 || (day == 29 && !(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))))) return false;

    // 30-day months check
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
    cout << "Passenger: " << passenger.name << "\n";
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
            cout << "Passenger: " << passenger.name << ", Flight: " << passenger.flightNumber
                << ", Fare: $" << fixed << setprecision(2) << passenger.fare
                << ", Booking Time: " << passenger.bookingTime << endl;
        }
    }
}

// Saving flight data to a file
void saveFlightData(const string& filename, const vector<Flight>& flights) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& flight : flights) {
            file << flight.flightNumber << "," << flight.origin << "," << flight.destination << ","
                << flight.baseFare << "," << flight.distance << "," << static_cast<int>(flight.fareClass)
                << "," << flight.isPeakSeason << endl;
        }
        file.close();
    }
    else {
        cout << "Unable to open file for saving data." << endl;
    }
}

// Loading flight data from a file
void loadFlightData(const string& filename, vector<Flight>& flights) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream stream(line);
        Flight flight;
        string fareClassStr;
        getline(stream, flight.flightNumber, ',');
        getline(stream, flight.origin, ',');
        getline(stream, flight.destination, ',');
        stream >> flight.baseFare;
        stream.ignore();  // Ignore comma
        stream >> flight.distance;
        stream.ignore();  // Ignore comma
        getline(stream, fareClassStr, ',');
        flight.fareClass = static_cast<FareClass>(stoi(fareClassStr));
        stream >> flight.isPeakSeason;
        flights.push_back(flight);
    }
}
