#include "user.h"
#include "carpool_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Constructor
User::User() : fullName("Guest User"), creditPoints(0), ratingScore(-1), loggedIn(false) {}

std::vector<User*> users;

// Validate the password based on a simple policy
bool User::isValidPassword(const std::string& password) {
    if (password.length() < 8) return false;

    bool hasDigit = false, hasUpper = false, hasLower = false;

    for (char c : password) {
        if (isdigit(c)) hasDigit = true;
        if (isupper(c)) hasUpper = true;
        if (islower(c)) hasLower = true;
    }

    return hasDigit && hasUpper && hasLower;
}

// Method to add credits
void User::addCreditPoints(int points) {
    creditPoints += points;
}

// Method to deduct credits
void User::deductCreditPoints(int points) {
    creditPoints -= points;
}

// Helper function to trim leading and trailing spaces
std::string User::trimSpaces(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";  // String is all spaces
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Get non-empty input from the user
std::string User::getNonEmptyInput(const std::string& prompt) {
    std::string input;
    do {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.empty()) {
            std::cout << "Input cannot be empty. Please try again.\n";
        }
    } while (input.empty());
    return input;
}

// User registration method
void User::registerUser() {
    username = getNonEmptyInput("Enter username: ");
    
    std::string tempPassword;
    while (true) {
        tempPassword = getNonEmptyInput("Enter password (at least 8 characters, one uppercase, one lowercase, one digit): ");
        if (isValidPassword(tempPassword)) {
            password = tempPassword;
            break;
        } else {
            std::cout << "Password must be at least 8 characters long, and contain at least one digit, one uppercase letter, and one lowercase letter.\n";
        }
    }

    fullName = getNonEmptyInput("Enter full name: ");
    phoneNumber = getNonEmptyInput("Enter phone number: ");
    email = getNonEmptyInput("Enter email: ");
    idType = getNonEmptyInput("Enter ID type (Citizen ID/Passport): ");
    idNumber = getNonEmptyInput("Enter " + idType + " number: ");

    creditPoints = 10;

    std::cout << "Registration successful! You have been charged $10, and your account has been credited with 10 points.\n";
    saveUserData();
}

// User login method
bool User::login(const std::string& enteredUsername, const std::string& enteredPassword) {
    std::ifstream inFile("users.txt");
    std::string line, fileUsername, filePassword;

    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
        loggedIn = false;
        return false;
    }

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::getline(ss, fileUsername, ',');
        std::getline(ss, filePassword, ',');

        if (enteredUsername == fileUsername && enteredPassword == filePassword) {
            // Load user data
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

            username = fileUsername;
            password = filePassword;
            std::cout << "Login successful!\n";
            loggedIn = true;
            return true;  // Set loggedIn to true upon successful login
        }
    }

    std::cout << "Login failed. Incorrect username or password.\n";
    loggedIn = false;  // Set loggedIn to false upon failed login
    return false;
}

// Save user data to file
void User::saveUserData() {
    std::ofstream outFile("users.txt", std::ios::app);

    if (outFile.is_open()) {
        outFile << username << "," << password << "," << fullName << "," << phoneNumber << ","
                << email << "," << idType << "," << idNumber << "," << creditPoints << "," << ratingScore << "," << ratingCount << "\n";  // Do not save loggedIn status
        outFile.close();
        std::cout << "User data saved successfully.\n";
    } else {
        std::cerr << "Error opening file for writing!\n";
    }
}

// View the user's profile
void User::viewProfile() {
    std::cout << "\nUser Profile\n";
    std::cout << "Username: " << username << "\n";
    std::cout << "Full Name: " << fullName << "\n";
    std::cout << "Phone Number: " << phoneNumber << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "ID Type: " << idType << "\n";
    std::cout << "ID Number: " << idNumber << "\n";
    std::cout << "Credit Points: " << creditPoints << "\n";
    std::cout << "Driver Rating: " << (ratingCount == 0 ? "N/A" : std::to_string(ratingScore)) 
              << " (based on " << ratingCount << " ratings)\n";
}


// Full update method for the user's profile (excluding password and username)
void User::updateProfile() {
    std::string input;

    input = getNonEmptyInput("Enter new full name (leave blank to keep unchanged): ");
    input = trimSpaces(input);
    if (!input.empty()) fullName = input;

    input = getNonEmptyInput("Enter new phone number (leave blank to keep unchanged): ");
    input = trimSpaces(input);
    if (!input.empty()) phoneNumber = input;

    input = getNonEmptyInput("Enter new email (leave blank to keep unchanged): ");
    input = trimSpaces(input);
    if (!input.empty()) email = input;

    input = getNonEmptyInput("Enter new ID type (leave blank to keep unchanged): ");
    input = trimSpaces(input);
    if (!input.empty()) idType = input;

    input = getNonEmptyInput("Enter new " + idType + " number (leave blank to keep unchanged): ");
    input = trimSpaces(input);
    if (!input.empty()) idNumber = input;

    saveUserData();
    std::cout << "Profile updated successfully.\n";
}

// Separate function to update the password
void User::updatePassword() {
    std::string oldPassword, newPassword;

    // Ask for old password
    std::cout << "Enter your old password: ";
    std::getline(std::cin, oldPassword);

    // Verify old password
    if (oldPassword != password) {
        std::cout << "Incorrect password.\n";
        return;
    }

    // Ask for new password
    while (true) {
        std::cout << "Enter new password (at least 8 characters, one uppercase, one lowercase, one digit): ";
        std::getline(std::cin, newPassword);

        if (isValidPassword(newPassword)) {
            password = newPassword;
            saveUserData();
            std::cout << "Password updated successfully.\n";
            break;
        } else {
            std::cout << "Password must be at least 8 characters long, and contain at least one digit, one uppercase letter, and one lowercase letter.\n";
        }
    }
}
void User::addDriverRating(int rating) {
    if (rating >= 1 && rating <= 5) {
        // Update the average rating using the formula
        ratingScore = (ratingScore * ratingCount + rating) / (ratingCount + 1);
        ratingCount++;  // Increment the number of ratings

        // Debugging print statement to verify the rating update
        std::cout << "New rating score: " << ratingScore << " based on " << ratingCount << " ratings.\n";
    } else {
        std::cerr << "Invalid rating! Please provide a rating between 1 and 5.\n";
    }
}

void viewAllUsers() {
    CarpoolManager* carpoolManager = CarpoolManager::getInstance();
    carpoolManager->loadUsersFromFile();  // Load users from file

    std::vector<User*>& users = carpoolManager->getUserList();  // Access the users list from the manager

    std::cout << "\n--- Registered Users ---\n";
    if (users.empty()) {
        std::cout << "No users are registered.\n";
        return;
    }

    // Display all users
    for (User* user : users) {
        user->viewProfile();  // Assuming viewProfile prints user details
    }
}


void removeUser() 
{
    CarpoolManager* carpoolManager = CarpoolManager::getInstance();
    carpoolManager->loadUsersFromFile();  // Ensure users are loaded from the file

    std::string usernameToRemove;
    std::cout << "Enter the username of the user to remove: ";
    std::getline(std::cin, usernameToRemove);

    std::vector<User*>& users = carpoolManager->getUserList();  // Access the users list from the manager

    bool userFound = false;

    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getUsername() == usernameToRemove) {
            delete *it;  // Free the memory
            users.erase(it);  // Remove from the users vector
            std::cout << "User '" << usernameToRemove << "' removed successfully.\n";
            userFound = true;
            break;
        }
    }

    if (!userFound) {
        std::cout << "User '" << usernameToRemove << "' not found.\n";
    }
}


