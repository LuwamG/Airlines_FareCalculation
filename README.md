Airlines_FareCalculation

Author: Luwam Gebrezgiabhier
Overview
This project simulates an airline fare calculation system, taking into account flight information, fare classes, seasonality, and seat demand. The program allows you to:

Calculate flight fares based on various factors.
Load and save flight data from a file (CSV format).
Manage dynamic memory using pointers and smart pointers.
Use structures, enumerations, arrays, and streams for data handling.
Features
Flight Fare Calculation:

Fares are calculated based on fare classes (Economy, Business, FirstClass), peak/off-peak season, and demand (remaining seats).
File Operations:

Save and load flight data from a CSV file.
Smart Pointers:

Dynamically allocate memory for flight data using smart pointers (std::unique_ptr).
Enumerations and Structures:

Use enumerations for fare classes and seasons.
Structures to manage flight and passenger data.
Prerequisites
To build and run this project, you need:

A C++ compiler (e.g., g++ for Linux/macOS or MinGW for Windows).
A C++11 or later standard is required.
File Structure
bash
Copy code

Functions
calculateFare()
Calculates the fare for a given flight based on:

Fare Class: Economy, Business, or FirstClass.
Season: Peak or OffPeak.
Demand: Adjusts the fare based on the number of remaining seats.
adjustPriceBasedOnDemand()
Adjusts the base fare based on the demand, which is calculated by the number of remaining seats compared to the total seats.

applySeasonalitySurcharge()
Applies a surcharge if the flight is in the peak season.

saveFlightData()
Saves flight data (flight number, origin, destination, base fare, distance, fare class, and season) to a file (flights.txt) in CSV format.

loadFlightData()
Loads flight data from the flights.txt file and stores it in a dynamically allocated array using std::unique_ptr.
