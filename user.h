#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string fullName;
    std::string username;
    std::string password;
    std::string phoneNumber;
    std::string email;
    std::string idType;
    std::string idNumber;
    int creditPoints;
    float ratingScore;
    int ratingCount;
    bool loggedIn;
    bool isAdmin;

    bool isValidPassword(const std::string& password);  // Check if password meets the required policy
    std::string trimSpaces(const std::string& str);     // Trim spaces from input
    std::string getNonEmptyInput(const std::string& prompt);  // Helper to get non-empty input

public:
    User();

    // Getters
    std::string getFullName() const { return fullName; }
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getPhoneNumber() const { return phoneNumber; }
    std::string getEmail() const { return email; }
    std::string getIdType() const { return idType; }
    std::string getIdNumber() const { return idNumber; }
    int getCreditPoints() const { return creditPoints; }     
    float getRatingScore() const { return ratingScore; }
    int getRatingCount() const { return ratingCount; }     
    bool isLoggedIn() const { return loggedIn; }             

    // Setters
    void setFullName(const std::string& name) { fullName = name; }
    void setUsername(const std::string& user) { username = user; }
    void setPassword(const std::string& pass) { password = pass; }
    void setPhoneNumber(const std::string& phone) { phoneNumber = phone; }
    void setEmail(const std::string& mail) { email = mail; }
    void setIdType(const std::string& type) { idType = type; }
    void setIdNumber(const std::string& id) { idNumber = id; }
    void setCreditPoints(int points) { creditPoints = points; }     
    void setRatingScore(float score) { ratingScore = score; } 
    void setRatingCount(int count) { ratingCount = count; }      
    void setLoggedIn(bool status) { loggedIn = status; }            

    //Core methods
    bool login(const std::string& user, const std::string& pass);
    void registerUser();
    void updateProfile();
    void updatePassword(); 
    void viewProfile();
    void saveUserData();
    void addDriverRating(int rating);
    void addCreditPoints(int points); 
    void deductCreditPoints(int points); 
    void viewAllUsers();
    void removeUser();
};

#endif // USER_H
