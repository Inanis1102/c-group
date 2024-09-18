#include "user.h"
#include <iostream>

using namespace std;

int main() {
    User user;
    int choice;
    bool isLoggedIn = false;
    string username, password;
    
    while (true) {
        cout << "\n--- Carpooling Application ---\n";
        cout << "1. Register as a new user\n";
        cout << "2. Login\n";
        cout << "3. View your profile (login required)\n";
        cout << "4. Update your profile (login required)\n";
        cout << "5. Purchase credit points (login required)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Clear input buffer
        
        switch (choice) {
            case 1:
                user.registerUser();
                break;
                
            case 2:
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);

                isLoggedIn = user.login(username, password);
                break;
                
            case 3:
                if (isLoggedIn) {
                    user.viewProfile();
                } else {
                    cout << "You must log in first.\n";
                }
                break;
                
            case 4:
                if (isLoggedIn) {
                    user.updateProfile();
                } else {
                    cout << "You must log in first.\n";
                }
                break;
                
            case 5:
                if (isLoggedIn) {
                    int amount;
                    cout << "Enter the number of credit points you want to purchase: ";
                    cin >> amount;
                    user.purchaseCredits(amount);
                } else {
                    cout << "You must log in first.\n";
                }
                break;
                
            case 6:
                cout << "Exiting...\n";
                return 0;
                
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
