#ifndef AIRLINES_FARECALCULATION_HPP
#define AIRLINES_FARECALCULATION_HPP

#include <iostream>
#include <string>
#include <memory>  
#include <iomanip>  

using namespace std;

// Enum for Fare Classes: Economy, Business, First Class
enum class FareClass {
    Economy = 1,  
    Business,    
    FirstClass    
};

// Flight structure to store flight details
struct Flight {
    string flightNumber;  
    string origin;       
    string destination;   
    double baseFare;      
    double distance;      
    FareClass fareClass;  
    bool isRefundable;    
};

// Passenger structure to store passenger booking details
struct Passenger {
    string firstName;      
    string lastName;       
    string flightNumber;   
    double totalFare;      
    double baggageFee;     
    string bookingTime;    
    FareClass fareClass;   
    double baggageWeight;  
};

// Function Prototypes (to be defined in the .cpp file)
double calculateFare(const Flight& flight, FareClass fareClass, const string& bookingTime,
    double baggageWeight, double baggageFee);
double calculateBaggageFee(double baggageWeight, double baggageLimit, double extraBaggageFeePerKg);
void addBookingToHistory(shared_ptr<Passenger> flightHistory[], int& passengerCount, shared_ptr<Passenger> passenger);
void displayPassengerDetails(const shared_ptr<Passenger>& passenger, const Flight& selectedFlight);
void displayFlightHistory(shared_ptr<Passenger> flightHistory[], int passengerCount);
int getValidIntegerInput(const string& prompt);
double getValidDoubleInput(const string& prompt);
string getValidDateInput();
void getValidUsername(string& firstName, string& lastName);

#endif
