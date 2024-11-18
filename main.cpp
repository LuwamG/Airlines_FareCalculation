#include "Airlines_FareCalculation.hpp"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main() {
    int flightCount = 3;

    // Dynamically allocate memory for the flights array
    unique_ptr<Flight[]> flights = make_unique<Flight[]>(flightCount);

    // Initialize some flight data
    flights[0] = { "AA101", "New York", "Los Angeles", 300.00, 2500, FareClass::Economy, Season::OffPeak };
    flights[1] = { "BA202", "London", "Paris", 150.00, 500, FareClass::Business, Season::Peak };
    flights[2] = { "CA303", "Tokyo", "Beijing", 200.00, 1000, FareClass::FirstClass, Season::OffPeak };

    // Calculate and display fares for each flight
    for (int i = 0; i < flightCount; ++i) {
        double fare = calculateFare(flights[i], flights[i].fareClass, "2023-12-15");
        cout << "Flight: " << flights[i].flightNumber << ", Fare: $" << fare << endl;
    }

    // Save flight data to a file
    saveFlightData("flights.txt", flights, flightCount);

    // Load flight data from a file
    unique_ptr<Flight[]> loadedFlights;
    int loadedSize = 0;
    loadFlightData("flights.txt", loadedFlights, loadedSize);

    // Display loaded flights
    for (int i = 0; i < loadedSize; ++i) {
        cout << "Loaded Flight: " << loadedFlights[i].flightNumber << ", "
            << loadedFlights[i].origin << " to " << loadedFlights[i].destination << endl;
    }

    return 0;
}
