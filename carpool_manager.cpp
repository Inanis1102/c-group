#include "carpool_manager.h"
#include "user.h"
#include <iostream>
#include <algorithm>

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
    carpoolListings.push_back(carpool);
}

// Get reference to the carpool listings
std::vector<Carpool*>& CarpoolManager::getCarpoolListings() {
    return carpoolListings;
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
    for (Carpool* carpool : carpoolListings) {
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
    for (Carpool* carpool : carpoolListings) {
        if (carpool->getDriverUsername() == user.getFullName()) {
            if (carpool->getAvailableSeats() == 0 || carpool->bookings.size() > 0) {
                std::cout << "You cannot unlist this carpool because some seats have been booked.\n";
                return false;
            }

            // Remove the carpool from the listings
            carpoolListings.erase(std::remove(carpoolListings.begin(), carpoolListings.end(), carpool), carpoolListings.end());
            std::cout << "Carpool unlisted successfully.\n";
            return true;
        }
    }

    std::cout << "You have no carpool listings to unlist.\n";
    return false;
}
