#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username;
    std::string password;
    std::string fullName;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    int creditPoints;
    float ratingScore;
    bool isVerified;

    // Private method to validate the password
    bool isValidPassword(const std::string& password);

    // Private method to get non-empty input
    std::string getNonEmptyInput(const std::string& prompt);

    // Private method to trim spaces from input
    std::string trimSpaces(const std::string& str);

public:
    // Constructor
    User();

    // User registration method
    void registerUser();

    // User login method
    bool login(const std::string& enteredUsername, const std::string& enteredPassword);

    // Save user data to file
    void saveUserData();

    // View the user's profile
    void viewProfile();

    // Update the user's profile (excluding password)
    void updateProfile();

    // Update the user's password
    void updatePassword();

    // Purchase additional credit points
    void purchaseCredits(int amount);

    std::string getFullName() const {return fullName;}
};

#endif // USER_H
