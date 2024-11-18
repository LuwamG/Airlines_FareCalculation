#include "Airlines_FareCalculation.hpp"
#include <iostream>
#include <fstream>

using namespace std;

// Calculate the fare based on various parameters
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageFee, short remainingSeats, short totalSeats, double baggageWeight,
    double extraBaggageFeePerKg, double baggageLimit) {
    double totalFare = flight.baseFare;

    // Adjust based on fare class
    switch (fareClass) {
    case FareClass::Economy:
        totalFare *= 1.0; // No change for Economy class
        break;
    case FareClass::Business:
        totalFare *= 1.5; // 50% more for Business class
        break;
    case FareClass::FirstClass:
        totalFare *= 2.0; // 100% more for First Class
        break;
    }

    // Apply peak season surcharge
    if (flight.isPeakSeason) {
        totalFare *= 1.3; // Increase by 30% during peak season
    }

    // Apply dynamic pricing based on remaining seats
    if (remainingSeats < totalSeats / 4) {
        totalFare *= 1.2; // Increase by 20% due to high demand
    }

    // Distance surcharge for long flights
    if (flight.distance > 2000) {
        totalFare += 100.0; // Add $100 for long-haul flights
    }

    // Add regular baggage fee
    totalFare += baggageFee;

    // Calculate and apply extra baggage fee if applicable
    if (baggageWeight > baggageLimit) {
        double extraWeight = baggageWeight - baggageLimit;
        totalFare += extraWeight * extraBaggageFeePerKg; // Add extra baggage fee
    }

    return totalFare;
}

// Display the passenger details after calculating the fare
void displayPassengerDetails(const Passenger& passenger, const Flight& flight, double baggageWeight, double baggageFee) {
    cout << "\n--- Passenger Fare Summary ---\n";
    cout << "Passenger: " << passenger.name << "\n";
    cout << "Flight Number: " << passenger.flightNumber << "\n";
    cout << "From: " << flight.origin << " to " << flight.destination << "\n";
    cout << "Fare Class: " << (flight.fareClass == FareClass::Economy ? "Economy" :
        flight.fareClass == FareClass::Business ? "Business" : "First Class") << "\n";
    cout << "Booking Time: " << passenger.bookingTime << "\n";
    cout << "Baggage Weight: " << baggageWeight << " kg\n";
    cout << "Baggage Fee: $" << baggageFee << "\n";
    cout << "Total Fare: $" << passenger.fare << "\n";
}

// Function to save flight data to a file
void saveFlightData(const string& filename, const vector<Flight>& flights) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for saving flight data.\n";
        return;
    }

    for (const auto& flight : flights) {
        outFile << flight.flightNumber << "," << flight.origin << "," << flight.destination
            << "," << flight.baseFare << "," << flight.distance << ","
            << static_cast<int>(flight.fareClass) << "," << flight.isPeakSeason << "\n";
    }
    outFile.close();
}

// Function to load flight data from a file
void loadFlightData(const string& filename, vector<Flight>& flights) {
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Error opening file for loading flight data.\n";
        return;
    }

    Flight flight;
    int fareClass;
    while (inFile >> flight.flightNumber >> flight.origin >> flight.destination
        >> flight.baseFare >> flight.distance >> fareClass >> flight.isPeakSeason) {
        flight.fareClass = static_cast<FareClass>(fareClass);
        flights.push_back(flight);
    }

    inFile.close();
}
