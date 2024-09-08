#include <iostream>
#include <fstream>
#include <string>

// User class definition
class User {
public:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    int creditPoints;

    // Constructor
    User(std::string uname, std::string pwd, std::string fname, std::string phone, 
         std::string mail, std::string idT, std::string idN) : 
         username(uname), password(pwd), fullName(fname), phoneNumber(phone), 
         email(mail), idType(idT), idNumber(idN), creditPoints(10) {}

    // Method to display user profile information (for testing purpose)
    void displayProfile() {
        std::cout << "Username: " << username << std::endl;
        std::cout << "Full Name: " << fullName << std::endl;
        std::cout << "Phone Number: " << phoneNumber << std::endl;
        std::cout << "Email: " << email << std::endl;
        std::cout << "ID Type: " << idType << std::endl;
        std::cout << "ID Number: " << idNumber << std::endl;
        std::cout << "Credit Points: " << creditPoints << std::endl;
    }
};

// Function to validate the password
bool isValidPassword(const std::string& password) {
    if (password.length() < 8) return false;

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSpecial = true;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

// Function to save user data to a file
void saveUserData(const User& user) {
    std::ofstream outFile("users.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << user.username << " " << user.password << " " << user.fullName << " "
                << user.phoneNumber << " " << user.email << " " << user.idType << " "
                << user.idNumber << " " << user.creditPoints << "\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

// Function to handle user registration
void registerUser() {
    std::string uname, pwd, fname, phone, mail, idT, idN;

    std::cout << "Enter username: ";
    std::cin >> uname;

    do {
        std::cout << "Enter password: ";
        std::cin >> pwd;
        if (!isValidPassword(pwd)) {
            std::cout << "Password must be at least 8 characters long, and contain an uppercase letter, "
                      << "a lowercase letter, a digit, and a special character.\n";
        }
    } while (!isValidPassword(pwd));

    std::cout << "Enter full name: ";
    std::cin.ignore();
    std::getline(std::cin, fname);

    std::cout << "Enter phone number: ";
    std::cin >> phone;

    std::cout << "Enter email: ";
    std::cin >> mail;

    std::cout << "Enter ID type (Citizen ID/Passport): ";
    std::cin >> idT;

    std::cout << "Enter ID/Passport number: ";
    std::cin >> idN;

    User newUser(uname, pwd, fname, phone, mail, idT, idN);
    saveUserData(newUser);

    std::cout << "Registration successful! You have been charged $10 and received 10 credit points.\n";
}
