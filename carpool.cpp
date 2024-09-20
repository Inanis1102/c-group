#include "carpool.h"
#include <iostream>
#include <fstream>

// Constructor
Carpool::Carpool(): availableSeats(0), contributionAmount(0), currentRating(0.0), ratingCount(0) {};

// Create a new carpool listing
void Carpool::createCarpool(const std::string& driverUsername) {
    this->driverUsername = driverUsername;

    std::cout << "Enter departure location: ";
    std::getline(std::cin, departureLocation);

    std::cout << "Enter destination location: ";
    std::getline(std::cin, destinationLocation);

    std::cout << "Enter date (e.g., 2024-09-20): ";
    std::getline(std::cin, date);

    std::cout << "Enter vehicle model: ";
    std::getline(std::cin, vehicleModel);

    std::cout << "Enter vehicle color: ";
    std::getline(std::cin, vehicleColor);

    std::cout << "Enter vehicle plate number: ";
    std::getline(std::cin, vehiclePlateNumber);

    std::cout << "Enter available seats: ";
    std::cin >> availableSeats;
    std::cin.ignore();  // Clear the newline character from the input buffer

    std::cout << "Enter contribution amount per passenger (in credit points): ";
    std::cin >> contributionAmount;
    std::cin.ignore();  // Clear the newline character from the input buffer

    std::cout << "Carpool created successfully!\n";

    // Write the carpool details to carpool.txt
    saveCarpoolToFile();    
}

//Save carpool to File
void Carpool::saveCarpoolToFile() const {
    std::ofstream outfile("carpool.txt", std::ios::app);
        if (outfile.is_open()) {
            outfile << driverUsername << "," << departureLocation << "," << destinationLocation << "," << date << ","
                    << vehicleModel << "," << vehicleColor << "," << vehiclePlateNumber << "," << availableSeats << ","
                    << contributionAmount << "," << currentRating << "," << ratingCount << "\n";  // Include rating details
            outfile.close();
            std::cout << "Carpool details saved to carpool.txt.\n";
        } else {
            std::cerr << "Error opening carpool.txt for writing.\n";
    }
}

// Display the details of the carpool listing
void Carpool::displayCarpoolDetails() const {
    std::cout << "\nCarpool Details:\n";
    std::cout << "Driver Username: " << driverUsername << "\n";
    std::cout << "Departure Location: " << departureLocation << "\n";
    std::cout << "Destination Location: " << destinationLocation << "\n";
    std::cout << "Date: " << date << "\n";
    std::cout << "Vehicle Model: " << vehicleModel << "\n";
    std::cout << "Vehicle Color: " << vehicleColor << "\n";
    std::cout << "Vehicle Plate Number: " << vehiclePlateNumber << "\n";
    std::cout << "Available Seats: " << availableSeats << "\n";
    std::cout << "Contribution per Passenger: " << contributionAmount << " credit points\n";
    std::cout << "Current Rating: " << currentRating << " (based on " << ratingCount << " ratings)\n";  // Show ratings
}

// Add a booking to the carpool
bool Carpool::addBooking(const std::string& passengerUsername) {
    if (availableSeats > 0) {
        Booking* newBooking = new Booking(passengerUsername, this);
        bookings.push_back(newBooking);
        availableSeats--;  // Reduce available seats
        std::cout << "Booking successful for " << passengerUsername << ".\n";
        return true;
    } else {
        std::cout << "No available seats for this carpool.\n";
        return false;
    }
}

// Add a rating to the carpool and recalculate the average
void Carpool::addRating(int rating) {
    if (rating >= 1 && rating <= 5) {
        currentRating = (currentRating * ratingCount + rating) / (ratingCount + 1);
        ratingCount++;
    } else {
        std::cerr << "Invalid rating! Please provide a rating between 1 and 5.\n";
    }
}

// Preload carpool from instance
void Carpool::preloadCarpool(const std::string& driverUsername, const std::string& departure, const std::string& destination,
                             const std::string& date, const std::string& model, const std::string& color, const std::string& plate, 
                             int seats, int contribution, double rating, int ratingCount) {
    this->driverUsername = driverUsername;
    this->departureLocation = departure;
    this->destinationLocation = destination;
    this->date = date;
    this->vehicleModel = model;
    this->vehicleColor = color;
    this->vehiclePlateNumber = plate;
    this->availableSeats = seats;
    this->contributionAmount = contribution;
    this->currentRating = rating;      
    this->ratingCount = ratingCount;   
}

