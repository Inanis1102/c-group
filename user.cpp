#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor
User::User() : creditPoints(0), ratingScore(-1), isVerified(false) {}

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

// Helper function to trim leading and trailing spaces
std::string User::trimSpaces(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";  // String is all spaces
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
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

// Save user data to file
void User::saveUserData() {
    std::ofstream outFile("users.txt", std::ios::app);

    if (outFile.is_open()) {
        outFile << username << "," << password << "," << fullName << "," << phoneNumber << ","
                << email << "," << idType << "," << idNumber << "," << creditPoints << "," << ratingScore << "," << isVerified << "\n";
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
    std::cout << "Rating Score: " << (ratingScore == -1 ? "N/A" : std::to_string(ratingScore)) << "\n";
    std::cout << "Verified: " << (isVerified ? "Yes" : "No") << "\n";
}

// User login method
bool User::login(const std::string& enteredUsername, const std::string& enteredPassword) {
    std::ifstream inFile("users.txt");
    std::string line, fileUsername, filePassword;

    if (!inFile) {
        std::cerr << "Error opening file for reading.\n";
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
            ss >> creditPoints >> ratingScore >> isVerified;

            username = fileUsername;
            password = filePassword;
            std::cout << "Login successful!\n";
            return true;
        }
    }

    std::cout << "Login failed. Incorrect username or password.\n";
    return false;
}

// Full update method for the user's profile with blank input handling
void User::updateProfile() {
    std::string input;

    input = getNonEmptyInput("Enter new username (leave blank to keep unchanged): ");
    input = trimSpaces(input);
    if (!input.empty()) username = input;

    input = getNonEmptyInput("Enter new password (leave blank to keep unchanged): ");
    input = trimSpaces(input);
    if (!input.empty()) password = input;

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

// Purchase additional credit points
void User::purchaseCredits(int amount) {
    creditPoints += amount;
    std::cout << "You have purchased " << amount << " credit points. Total credit points: " << creditPoints << "\n";
    saveUserData();
}
