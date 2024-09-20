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

std::vector<User*>& CarpoolManager::getUserList() {
    return users;
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

    bool isLoggedIn = user.isLoggedIn();

    std::vector<Carpool*> matchingCarpools;
    for (Carpool* carpool : this->carpoolListings) {
        // Skip the user's own carpool
        if (carpool->getDriverName() == user.getFullName()) {
            continue;
        }

        // Check if the carpool matches the search criteria and has available seats
        if (carpool->getAvailableSeats() > 0 &&
            carpool->getDepartureLocation() == departure &&
            carpool->getDestinationLocation() == destination &&
            carpool->getDate() == date) {

            // For non-logged-in users, only include carpools with a rating <= 3
            if (!isLoggedIn && carpool->getCurrentRating() > 3) {
                continue;  // Skip carpools with a rating greater than 3 for non-logged-in users
            }

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
        std::cout << "\n";
    }

    // Ask the user to choose a carpool
    int choice;
    std::cout << "Enter the number of the carpool you want to book: ";
    std::cin >> choice;
    std::cin.ignore();  // Clear the input buffer

    // Validate user choice
    if (choice < 1 || choice > matchingCarpools.size()) {
        std::cout << "Invalid choice.\n";
        return;
    }

    // Grab the selected carpool for booking
    Carpool* selectedCarpool = matchingCarpools[choice - 1];
    int requiredCredits = selectedCarpool->getContributionAmount();

    // Check if user has enough credits
    while (user.getCreditPoints() < requiredCredits) {
        std::cout << "You do not have enough credits to book this carpool.\n";
        std::cout << "You need " << requiredCredits << " credits, but you only have " << user.getCreditPoints() << ".\n";
        std::cout << "Please purchase more credits.\n";
        int additionalCredits;
        std::cout << "Enter the number of credits you want to purchase: ";
        std::cin >> additionalCredits;
        std::cin.ignore();  // Clear the input buffer

        user.addCreditPoints(additionalCredits);
        std::cout << "You now have " << user.getCreditPoints() << " credits.\n";
    }

    // Proceed with the booking once credits are sufficient
    if (selectedCarpool->addBooking(user.getFullName())) {
        // Deduct credits from user
        user.deductCreditPoints(requiredCredits);
        std::cout << "Booking confirmed for " << user.getFullName() << ".\n";

        // Prompt user to rate the carpool after booking
        int rating;
        std::cout << "Please rate the carpool (1 to 5): ";
        std::cin >> rating;
        std::cin.ignore();  // Clear the input buffer

        while (rating < 1 || rating > 5) {
            std::cout << "Invalid rating. Please enter a number between 1 and 5: ";
            std::cin >> rating;
            std::cin.ignore();
        }

        selectedCarpool->addRating(rating);
        std::cout << "Thank you! The carpool now has a rating of " << selectedCarpool->getCurrentRating() << ".\n";
    
        // Rate the driver after rating the carpool
        std::cout << "Please rate the driver (1 to 5): ";
        int driverRating;
        std::cin >> driverRating;
        std::cin.ignore();  // Clear the input buffer

        while (driverRating < 1 || driverRating > 5) {
            std::cout << "Invalid rating. Please enter a number between 1 and 5: ";
            std::cin >> driverRating;
            std::cin.ignore();
        }

        // Find the driver and update their rating
        User* driver = getDriverFullName(selectedCarpool->getDriverName());
        if (driver != nullptr) {
            driver->addDriverRating(driverRating);  // Add the rating for the driver

            // Display the updated rating
            std::cout << "Thank you! The driver now has a rating of " << driver->getRatingScore() 
              << "\n";
        } else {
        std::cout << "Driver not found!\n";
        }

    } else {
        std::cout << "Booking failed.\n";
    }
}

// Unlist a carpool
bool CarpoolManager::unlistCarpool(User& user) {
    for (Carpool* carpool : this->carpoolListings) {
        if (carpool->getDriverName() == user.getFullName()) {
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
        double rating = 0.0;  // New: to store the current rating
        int ratingCount = 0;  // New: to store the number of ratings

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

        if (ss.peek() == ',') ss.ignore();  
        if (!(ss >> contribution)) {
            std::cout << "Error: Failed to parse contribution. Skipping line.\n";
            continue;
        }

        if (ss.peek() == ',') ss.ignore(); 

        // Read rating and rating count from file
        if (!(ss >> rating)) {
            std::cout << "Error: Failed to parse rating. Skipping line.\n";
            continue;
        }

        if (ss.peek() == ',') ss.ignore();  

        if (!(ss >> ratingCount)) {
            std::cout << "Error: Failed to parse rating count. Skipping line.\n";
            continue;
        }

        // Create new carpool using the preloadCarpool method
        Carpool* carpool = new Carpool();
        carpool->preloadCarpool(driverUsername, departure, destination, date, model, color, plate, seats, contribution, rating, ratingCount);

        // Add the carpool to the CarpoolManager
        this->addCarpool(carpool);
        loadedCount++;
    }

    infile.close();
}

// method to search for driver with a certain name
User* CarpoolManager::getDriverFullName(const std::string& fullName) {
    loadUsersFromFile();
    for (User* user : users) {
        std::string userFullName = user->getFullName();
        
        // Compare names after trimming spaces and ignoring case (if needed)
        if (trimSpaces(userFullName) == trimSpaces(fullName)) {
            return user;
        }
    }
    std::cout << "Driver not found for full name: " << fullName << "|\n";
    return nullptr;
}

// Define trimSpaces as a member function of CarpoolManager
std::string CarpoolManager::trimSpaces(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";  // String is all spaces
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

void CarpoolManager::loadUsersFromFile() {

    users.clear();

    std::ifstream inFile("users.txt");
    if (!inFile.is_open()) {
        std::cerr << "Could not open users.txt file.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string username, password, fullName, phoneNumber, email, idType, idNumber;
        int creditPoints;
        float ratingScore;
        int ratingCount;

        // Read user details from the file
        std::getline(ss, username, ',');
        std::getline(ss, password, ',');
        std::getline(ss, fullName, ',');
        std::getline(ss, phoneNumber, ',');
        std::getline(ss, email, ',');
        std::getline(ss, idType, ',');
        std::getline(ss, idNumber, ',');
        // Handle numeric values with ss.peek()
        if (!(ss >> creditPoints)) {
            std::cerr << "Error reading creditPoints for user: " << username << "\n";
            continue;
        }
        if (ss.peek() == ',') ss.ignore();  // Ignore extra comma after creditPoints

        if (!(ss >> ratingScore)) {
            std::cerr << "Error reading ratingScore for user: " << username << "\n";
            continue;
        }
        if (ss.peek() == ',') ss.ignore();  // Ignore extra comma after ratingScore

        if (!(ss >> ratingCount)) {
            std::cerr << "Error reading ratingCount for user: " << username << "\n";
            continue;
        }

        // Create a new User object
        User* newUser = new User();
        newUser->setUsername(username);
        newUser->setPassword(password);
        newUser->setFullName(fullName);
        newUser->setPhoneNumber(phoneNumber);
        newUser->setEmail(email);
        newUser->setIdType(idType);
        newUser->setIdNumber(idNumber);
        newUser->setCreditPoints(creditPoints);
        newUser->setRatingScore(ratingScore);
        newUser->setRatingCount(ratingCount);

        // Add the new user to the users vector
        users.push_back(newUser);
    }

    inFile.close();
}
