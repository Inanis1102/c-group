#include "carpool_manager.h"
#include "user.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

// Initialize the static instance
CarpoolManager* CarpoolManager::instance = nullptr;

// Get the singleton instance
CarpoolManager* CarpoolManager::getInstance() {
    if (instance == nullptr) {
        instance = new CarpoolManager();
    }
    return instance;
}

// Add a carpool to the listings
void CarpoolManager::addCarpool(Carpool* carpool) {
    this->carpoolListings.push_back(carpool);  // Use this->carpoolListings
}

// Get reference to the carpool listings
std::vector<Carpool*>& CarpoolManager::getCarpoolListings() {
    return this->carpoolListings;  // Use this->carpoolListings
}

// Search and book a carpool
void CarpoolManager::searchAndBookCarpool(User& user) {
    std::string departure, destination, date;
    std::cout << "Enter departure location: ";
    std::getline(std::cin, departure);
    std::cout << "Enter destination location: ";
    std::getline(std::cin, destination);
    std::cout << "Enter date (e.g., 2024-09-20): ";
    std::getline(std::cin, date);

    std::vector<Carpool*> matchingCarpools;
    for (Carpool* carpool : this->carpoolListings) {
        // Skip the user's own carpool
        if (carpool->getDriverUsername() == user.getFullName()) {
            continue;
        }

        // Check if the carpool matches the search criteria and has available seats
        if (carpool->getAvailableSeats() > 0 &&
            carpool->getDepartureLocation() == departure &&
            carpool->getDestinationLocation() == destination &&
            carpool->getDate() == date) {
            matchingCarpools.push_back(carpool);
        }
    }

    // If no carpools are found
    if (matchingCarpools.empty()) {
        std::cout << "No carpools available for the given search criteria.\n";
        return;
    }

    // Display matching carpools with numbers for user selection
    std::cout << "\nAvailable Carpools:\n";
    for (size_t i = 0; i < matchingCarpools.size(); ++i) {
        std::cout << i + 1 << ". ";
        matchingCarpools[i]->displayCarpoolDetails();
    }
    std::cout <<"\n";

    // Ask the user to choose a carpool
    int choice;
    std::cout << "\nEnter the number of the carpool you want to book: ";
    std::cin >> choice;
    std::cin.ignore();  // Clear the input buffer

    // Validate user choice
    if (choice < 1 || choice > matchingCarpools.size()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    // Book the selected carpool
    Carpool* selectedCarpool = matchingCarpools[choice - 1];
    if (selectedCarpool->addBooking(user.getFullName())) {
        std::cout << "Booking confirmed for " << user.getFullName() << ".\n";
    } else {
        std::cout << "Booking failed.\n";
    }
}

// Unlist a carpool
bool CarpoolManager::unlistCarpool(User& user) {
    for (Carpool* carpool : this->carpoolListings) {
        if (carpool->getDriverUsername() == user.getFullName()) {
            if (carpool->getAvailableSeats() == 0 || carpool->bookings.size() > 0) {
                std::cout << "You cannot unlist this carpool because some seats have been booked.\n";
                return false;
            }

            // Remove the carpool from the listings
            this->carpoolListings.erase(
                std::remove(this->carpoolListings.begin(), this->carpoolListings.end(), carpool),
                this->carpoolListings.end()
            );
            std::cout << "Carpool unlisted successfully.\n";
            return true;
        }
    }

    std::cout << "You have no carpool listings to unlist.\n";
    return false;
}

//load premade carpool from carpool.txt for teesting purposes
void CarpoolManager::loadCarpoolsFromFile() {
    std::ifstream infile("carpool.txt");

    if (!infile.is_open()) {
        std::cout << "No pre-made carpool listings found (carpool.txt not found).\n";
        return;
    }

    std::string line;
    int loadedCount = 0;

    // Clear existing carpool listings to avoid duplication
    carpoolListings.clear();  

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string driverUsername, departure, destination, date, model, color, plate;
        int seats = 0, contribution = 0;

        // Read carpool details from file
        std::getline(ss, driverUsername, ',');
        std::getline(ss, departure, ',');
        std::getline(ss, destination, ',');
        std::getline(ss, date, ',');
        std::getline(ss, model, ',');
        std::getline(ss, color, ',');
        std::getline(ss, plate, ',');

        if (!(ss >> seats)) {
            std::cout << "Error: Failed to parse seats. Skipping line.\n";
            continue;
        }

        if (ss.peek() == ',') {
            ss.ignore();
        }

        if (!(ss >> contribution)) {
            std::cout << "Error: Failed to parse contribution. Skipping line.\n";
            continue;
        }

        // Create new carpool using the preloadCarpool method
        Carpool* carpool = new Carpool();
        carpool->preloadCarpool(driverUsername, departure, destination, date, model, color, plate, seats, contribution);

        // Add the carpool to the CarpoolManager
        this->addCarpool(carpool);
        loadedCount++;
    }

    infile.close();

    std::cout << "Pre-made carpools loaded from carpool.txt: " << loadedCount << "\n";
}
