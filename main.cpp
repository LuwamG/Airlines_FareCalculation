#include <iostream>
#include <fstream>
#include <memory>
#include "Airlines_FareCalculation.hpp"

using namespace std;

int main() {
    // Flight data initialization
    int flightCount = 3;
    int remainingSeats = 50; 
    int totalSeats = 100;    
    unique_ptr<Flight[]> flights = make_unique<Flight[]>(flightCount);

    flights[0] = { "AA101", "New York", "Los Angeles", 300.00, 2500, FareClass::Economy, false };
    flights[1] = { "BA202", "London", "Paris", 150.00, 500, FareClass::Business, true };
    flights[2] = { "CA303", "Tokyo", "Beijing", 200.00, 1000, FareClass::FirstClass, false };

    // Display flight details
    for (int i = 0; i < flightCount; ++i) {
        displayFlightDetails(flights[i]);
        cout << "--------------------" << endl;
    }

    // Create passenger data
    Passenger passenger1 = { "John Doe", "AA101", 0.0, 50.0, "2023-12-01" };
    Passenger passenger2 = { "Jane Smith", "BA202", 0.0, 40.0, "2023-12-05" };
    Passenger passenger3 = { "Alice Johnson", "CA303", 0.0, 60.0, "2023-12-10" };

    // Display passenger details (including fare)
    displayPassengerDetails(passenger1, flights[0], passenger1.baggageFee);
    displayPassengerDetails(passenger2, flights[1], passenger2.baggageFee);
    displayPassengerDetails(passenger3, flights[2], passenger3.baggageFee);

    // Save flight data to a file
    ofstream outFile("flights.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < flightCount; ++i) {
            outFile << flights[i].flightNumber << ","
                << flights[i].origin << ","
                << flights[i].destination << ","
                << flights[i].baseFare << ","
                << flights[i].distance << ","
                << (flights[i].fareClass == FareClass::Economy ? "Economy" :
                    (flights[i].fareClass == FareClass::Business ? "Business" : "FirstClass")) << ","
                << (flights[i].isPeakSeason ? "Yes" : "No") << endl;
        }
        cout << "Flight data saved successfully!" << endl;
        outFile.close();
    }
    else {
        cout << "Error saving flight data!" << endl;
    }

    return 0;
}
