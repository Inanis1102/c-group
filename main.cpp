#include <iostream>
#include "user.cpp"
#include "carpool.cpp"

// Forward declarations of functions
void registerUser();
void createCarpool(const User& driver);

int main() {
    registerUser();  // Register a user first

    // Create a carpool listing for the registered user
    std::string continueOption;
    std::cout << "Do you want to create a carpool listing? (yes/no): ";
    std::cin >> continueOption;

    if (continueOption == "yes") {
        // Assuming you want to use the last registered user as the driver
        std::string username = "exampleUser"; // Replace with logic to get the current user
        User driver(username, "password", "Full Name", "1234567890", "email@example.com", "ID", "ID12345");
        createCarpool(driver);
    }

    return 0;
}
