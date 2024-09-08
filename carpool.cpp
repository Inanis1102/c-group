#include <iostream>
#include <fstream>
#include <string>
#include "user.cpp"

// Carpool class definition
class Carpool {
public:
    std::string driverUsername;
    std::string departureLocation;
    std::string destinationLocation;
    std::string date;
    std::string vehicleModel;
    std::string vehicleColor;
    std::string vehiclePlateNumber;
    int availableSeats;
    int contributionPerPassenger;

    // Constructor
    Carpool(std::string driver, std::string depLoc, std::string destLoc, std::string dt, 
            std::string model, std::string color, std::string plate, int seats, int contribution) : 
            driverUsername(driver), departureLocation(depLoc), destinationLocation(destLoc), 
            date(dt), vehicleModel(model), vehicleColor(color), vehiclePlateNumber(plate), 
            availableSeats(seats), contributionPerPassenger(contribution) {}

    // Method to display carpool details
    void displayCarpool() {
        std::cout << "Driver: " << driverUsername << std::endl;
        std::cout << "From: " << departureLocation << std::endl;
        std::cout << "To: " << destinationLocation << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "Vehicle: " << vehicleModel << " (" << vehicleColor << ") - Plate: " << vehiclePlateNumber << std::endl;
        std::cout << "Available Seats: " << availableSeats << std::endl;
        std::cout << "Contribution per Passenger: " << contributionPerPassenger << " credit points" << std::endl;
    }
};

// Function to save carpool data to a file
void saveCarpoolData(const Carpool& carpool) {
    std::ofstream outFile("carpools.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << carpool.driverUsername << " " << carpool.departureLocation << " "
                << carpool.destinationLocation << " " << carpool.date << " "
                << carpool.vehicleModel << " " << carpool.vehicleColor << " "
                << carpool.vehiclePlateNumber << " " << carpool.availableSeats << " "
                << carpool.contributionPerPassenger << "\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

// Function to create a carpool listing
void createCarpool(const User& driver) {
    std::string depLoc, destLoc, dt, model, color, plate;
    int seats, contribution;

    std::cout << "Enter departure location: ";
    std::cin.ignore();
    std::getline(std::cin, depLoc);

    std::cout << "Enter destination location: ";
    std::getline(std::cin, destLoc);

    std::cout << "Enter date: ";
    std::getline(std::cin, dt);

    std::cout << "Enter vehicle model: ";
    std::getline(std::cin, model);

    std::cout << "Enter vehicle color: ";
    std::getline(std::cin, color);

    std::cout << "Enter vehicle plate number: ";
    std::getline(std::cin, plate);

    std::cout << "Enter number of available seats: ";
    std::cin >> seats;

    std::cout << "Enter contribution amount per passenger (in credit points): ";
    std::cin >> contribution;

    Carpool newCarpool(driver.username, depLoc, destLoc, dt, model, color, plate, seats, contribution);
    saveCarpoolData(newCarpool);

    std::cout << "Carpool listing created successfully!\n";
}
