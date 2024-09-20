#include "carpool.h"
#include "user.h"
#include "carpool_manager.h"
#include "booking.h"
#include <iostream>
#include <vector>
#include <cstdlib> 

using namespace std;
 
void viewAllUsers();    
void viewAllCarpools(); 
void removeUser();      
void removeCarpool();
void mainMenu();

User user;
int choice;
bool isLoggedIn = false;
string username, password;
std::string adminUsername = "admin"; //admin login info for testing
std::string adminPassword = "admin";

void showAdminMenu() {
    int adminChoice;
    while (true) {
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. View all users\n";
        std::cout << "2. View all carpools\n";
        std::cout << "3. Remove a user\n";
        std::cout << "4. Remove a carpool\n";
        std::cout << "5. Logout\n";
        std::cout << "Enter your choice: ";
        std::cin >> adminChoice;
        std::cin.ignore();

        switch (adminChoice) {
            case 1:
                viewAllUsers();  
                break;
            case 2:
                viewAllCarpools();  
                break;
            case 3:
                removeUser();  
                break;
            case 4:
                removeCarpool();  
                break;
            case 5:
                std::cout << "Logging out of admin...\n";
                mainMenu();  // Exit admin menu
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

void mainMenu()
{
    while (true) {
        if (!isLoggedIn) {
            cout << "\n--- Carpooling Application ---\n";
            cout << "1. Register as a new user\n";
            cout << "2. Login\n";
            cout << "3. Search for carpool\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();  // Clear the input buffer

            switch (choice) {
                case 1:
                    user.registerUser();
                    break;

                case 2:
                    cout << "Enter username: ";
                    getline(cin, username);
                    cout << "Enter password: ";
                    getline(cin, password);
                    if (username == adminUsername && password == adminPassword)
                    {
                        showAdminMenu();
                        isLoggedIn=false;
                    }
                    else                    
                    {
                        isLoggedIn = user.login(username, password);
                        break;
                    }
                
                case 3:{
                    CarpoolManager* carpoolManager = CarpoolManager::getInstance();
                    carpoolManager->loadCarpoolsFromFile();  // Load carpools from file
                    carpoolManager->searchAndBookCarpool(user);  // Call searchAndBookCarpool for non-logged-in users
                    break;
                }

                case 4:
                    cout << "Exiting...\n";
                    exit(0);

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } else {
            CarpoolManager* carpoolManager = CarpoolManager::getInstance();
            // Load pre-made carpools from carpool.txt
            carpoolManager->loadCarpoolsFromFile();

            cout << "\n--- Carpooling Application (Logged in as " << user.getFullName() << ") ---\n";
            cout << "1. View your profile\n";
            cout << "2. Update your profile\n";
            cout << "3. Create a carpool listing\n";
            cout << "4. Search and book a carpool\n";
            cout << "5. Unlist a carpool\n";
            cout << "6. Logout\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore();  // Clear the input buffer

            switch (choice) {
                case 1:
                    user.viewProfile();
                    break;

                case 2:
                    user.updateProfile();
                    break;

                case 3:
                    {
                        Carpool* newCarpool = new Carpool();
                        newCarpool->createCarpool(user.getFullName());
                        carpoolManager->addCarpool(newCarpool);  // Add carpool to the manager
                        cout << "Carpool created successfully!\n";
                    }
                    break;

                case 4:
                    carpoolManager->searchAndBookCarpool(user);  // Call searchAndBookCarpool from CarpoolManager
                    break;

                case 5:
                    carpoolManager->unlistCarpool(user);  // Call unlistCarpool from CarpoolManager
                    break;

                case 6:
                    cout << "Logging out...\n";
                    isLoggedIn = false;  // Reset login state
                    break;

                case 7:
                    cout << "Exiting...\n";
                    return;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }
}



int main() 
{
    mainMenu();
}