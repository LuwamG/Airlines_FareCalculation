#include "Airlines_FareCalculation.hpp"

using namespace std;

double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    const double baggageFee, short remainingSeats, short totalSeats,
    double baggageWeight, const double extraBaggageFeePerKg, const double baggageLimit) {

    double totalFare = flight.baseFare;

    // Adjust for Fare Class
    if (fareClass == FareClass::Business) {
        totalFare *= 1.5; // Business class is 50% more expensive
    }
    else if (fareClass == FareClass::FirstClass) {
        totalFare *= 2.0; // First class is 100% more expensive
    }

    // Apply a surcharge for last-minute bookings
    if (isEarlyBooking(bookingTime)) {
        totalFare *= 0.90; // 10% discount for early booking
    }
    else {
        totalFare *= 1.10; // 10% surcharge for last-minute booking
    }

    // Adjust for peak season
    if (flight.isPeakSeason) {
        totalFare *= 1.20; // 20% surcharge during peak season
    }

    // Adjust for Distance
    totalFare += (flight.distance / 100) * 1.5; // Add $1.5 per 100km

    // Demand-based pricing
    if (remainingSeats < 20) {
        totalFare *= 1.10; // 10% increase when fewer than 20 seats are available
    }

    // Calculate baggage fees
    if (baggageWeight > baggageLimit) {
        totalFare += (baggageWeight - baggageLimit) * extraBaggageFeePerKg;
    }

    return totalFare;
}

bool isValidDate(const string& dateStr) {
    // Simple date validation: yyyy-mm-dd
    if (dateStr.length() != 10) return false;
    if (dateStr[4] != '-' || dateStr[7] != '-') return false;
    for (int i = 0; i < dateStr.length(); i++) {
        if (i != 4 && i != 7 && !isdigit(dateStr[i])) {
            return false;
        }
    }
    return true;
}

bool isEarlyBooking(const string& bookingTime) {
    // Assume the current date is '2024-12-01'
    const string currentDate = "2024-12-01";
    return bookingTime < currentDate; // If the booking is before the current date
}

void addBookingToHistory(vector<Passenger>& flightHistory, const Passenger& passenger) {
    flightHistory.push_back(passenger);
}

void displayPassengerDetails(const Passenger& passenger, const Flight& flight, double baggageWeight, double baggageFee) {
    cout << "Passenger Name: " << passenger.fullName << endl;
    cout << "Flight: " << flight.flightNumber << ", " << flight.origin << " to " << flight.destination << endl;
    cout << "Fare Class: " << (passenger.fareClass == FareClass::Economy ? "Economy" :
        passenger.fareClass == FareClass::Business ? "Business" : "First Class") << endl;
    cout << "Booking Time: " << passenger.bookingTime << endl;
    cout << "Baggage Weight: " << baggageWeight << "kg, Baggage Fee: $" << baggageFee << endl;
    cout << "Total Fare: $" << passenger.fare << endl;
}

void displayFlightHistory(const vector<Passenger>& flightHistory) {
    cout << "Booking History:\n";
    if (flightHistory.empty()) {
        cout << "No bookings found.\n";
        return;
    }
    for (const auto& passenger : flightHistory) {
        cout << passenger.fullName << " - " << passenger.flightNumber << " - " << passenger.bookingTime << endl;
    }
}

void saveFlightData(const string& filename, const vector<Flight>& flights) {
    ofstream outFile(filename, ios::binary);
    for (const auto& flight : flights) {
        outFile.write(reinterpret_cast<const char*>(&flight), sizeof(flight));
    }
    outFile.close();
}

void loadFlightData(const string& filename, vector<Flight>& flights) {
    ifstream inFile(filename, ios::binary);
    Flight flight;
    while (inFile.read(reinterpret_cast<char*>(&flight), sizeof(flight))) {
        flights.push_back(flight);
    }
    inFile.close();
}
