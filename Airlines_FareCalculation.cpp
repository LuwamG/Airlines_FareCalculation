#include "Airlines_FareCalculation.hpp"

double adjustFareBasedOnDistance(double fare, double distance) {
    if (distance > 2000) {
        fare += 100.0; // Extra charge for long-haul flights
    }
    return fare;
}

double adjustPriceBasedOnDemand(double fare, int remainingSeats, int totalSeats) {
    if (remainingSeats < totalSeats / 4) {
        fare *= 1.2;  // Increase price by 20% if there are fewer than 25% seats left
    }
    return fare;
}

double applySeasonalitySurcharge(double fare, bool isPeakSeason) {
    if (isPeakSeason) {
        fare *= 1.3;  // Increase fare by 30% during peak season
    }
    return fare;
}

double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime, double baggageFee) {
    double fare = flight.baseFare;

    // Adjust fare based on fare class
    switch (fareClass) {
    case FareClass::Economy: fare *= 1.0; break;
    case FareClass::Business: fare *= 1.5; break;
    case FareClass::FirstClass: fare *= 2.0; break;
    }

    // Adjust fare based on demand
    int remainingSeats = 50; // Example value
    int totalSeats = 100;    // Example value
    fare = adjustPriceBasedOnDemand(fare, remainingSeats, totalSeats);

    // Apply seasonality surcharge
    fare = applySeasonalitySurcharge(fare, flight.isPeakSeason);

    // Adjust fare based on distance
    fare = adjustFareBasedOnDistance(fare, flight.distance);

    // Add baggage fee
    fare += baggageFee;

    return fare;
}

void displayFlightDetails(const Flight& flight) {
    cout << "Flight Number: " << flight.flightNumber << endl;
    cout << "Origin: " << flight.origin << endl;
    cout << "Destination: " << flight.destination << endl;
    cout << "Base Fare: $" << flight.baseFare << endl;
    cout << "Distance: " << flight.distance << " miles" << endl;
    cout << "Fare Class: " << (flight.fareClass == FareClass::Economy ? "Economy" :
        (flight.fareClass == FareClass::Business ? "Business" : "FirstClass")) << endl;
    cout << "Peak Season: " << (flight.isPeakSeason ? "Yes" : "No") << endl;
}

void displayPassengerDetails(const Passenger& passenger, const Flight& flight, double baggageFee) {
    double totalFare = calculateFare(flight, FareClass::Economy, passenger.bookingTime, baggageFee);
    cout << "Passenger: " << passenger.name << endl;
    cout << "Flight: " << passenger.flightNumber << endl;
    cout << "Booking Time: " << passenger.bookingTime << endl;
    cout << "Total Fare: $" << totalFare << endl;
}
