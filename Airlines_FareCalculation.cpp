#include "Airlines_FareCalculation.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


using namespace std;

// Function to calculate the fare based on the flight details, fare class, and booking time
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime) {
    double fare = flight.baseFare;

    // Adjust based on the fare class
    switch (fareClass) {
    case FareClass::Economy:
        fare *= 1.0;  // No adjustment for economy
        break;
    case FareClass::Business:
        fare *= 1.5;  // Business class is 1.5 times the base fare
        break;
    case FareClass::FirstClass:
        fare *= 2.0;  // First class is 2 times the base fare
        break;
    }

    // Apply demand-based price adjustment (i.e., fewer seats, higher price)
    int remainingSeats = 50;  // Example value, can be adjusted based on the real seat count
    int totalSeats = 100;     // Total seats in the aircraft
    fare = adjustPriceBasedOnDemand(fare, remainingSeats, totalSeats);

    // Apply seasonality surcharge
    fare = applySeasonalitySurcharge(fare, flight.season);

    return fare;
}

// Function to adjust price based on remaining seats (higher price if fewer seats left)
double adjustPriceBasedOnDemand(double baseFare, int remainingSeats, int totalSeats) {
    double demandFactor = (static_cast<double>(totalSeats - remainingSeats) / totalSeats);
    return baseFare * (1 + demandFactor);  // Increase fare based on demand
}

// Function to apply a seasonality surcharge (higher fare in peak season)
double applySeasonalitySurcharge(double baseFare, Season season) {
    if (season == Season::Peak) {
        return baseFare * 1.25;  // 25% more in peak season
    }
    return baseFare;
}

// Function to save flight data to a file
void saveFlightData(const string& filename, unique_ptr<Flight[]>& flights, int size) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; ++i) {
            file << flights[i].flightNumber << ","
                << flights[i].origin << ","
                << flights[i].destination << ","
                << flights[i].baseFare << ","
                << flights[i].distance << ","
                << static_cast<int>(flights[i].fareClass) << ","
                << static_cast<int>(flights[i].season) << endl;
        }
        file.close();
        cout << "Flight data saved successfully!" << endl;
    }
    else {
        cout << "Error opening file for writing." << endl;
    }
}

// Function to load flight data from a file
void loadFlightData(const string& filename, unique_ptr<Flight[]>& flights, int& size) {
    ifstream file(filename);
    string line;
    size = 0;

    // First pass: count the number of lines (flights)
    while (getline(file, line)) {
        ++size;
    }

    // Reopen the file from the beginning
    file.close();
    file.open(filename);  // Reopen the file

    // Allocate memory for the flights array
    flights = make_unique<Flight[]>(size);

    // Second pass: populate the flights array
    int i = 0;
    while (getline(file, line) && i < size) {
        stringstream stream(line);
        string fareClassStr, seasonStr;

        // Parse flight data from CSV format
        getline(stream, flights[i].flightNumber, ',');
        getline(stream, flights[i].origin, ',');
        getline(stream, flights[i].destination, ',');
        stream >> flights[i].baseFare;
        stream.ignore(1, ',');
        stream >> flights[i].distance;
        stream.ignore(1, ',');
        getline(stream, fareClassStr, ',');
        getline(stream, seasonStr, ',');

        // Convert strings to enum
        flights[i].fareClass = static_cast<FareClass>(stoi(fareClassStr));
        flights[i].season = static_cast<Season>(stoi(seasonStr));

        ++i;
    }
    file.close();
    cout << "Flight data loaded successfully!" << endl;
}
