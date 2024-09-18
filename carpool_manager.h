#ifndef CARPOOL_MANAGER_H
#define CARPOOL_MANAGER_H

#include <vector>
#include "carpool.h"
#include "user.h"

class CarpoolManager {
private:
    static CarpoolManager* instance;  // Singleton instance
    std::vector<Carpool*> carpoolListings;  // Carpool listings

    // Private constructor to prevent instantiation
    CarpoolManager() {}

public:
    // Public static method to access the singleton instance
    static CarpoolManager* getInstance();

    // Add a carpool to the listings
    void addCarpool(Carpool* carpool);

    // Get reference to the carpool listings
    std::vector<Carpool*>& getCarpoolListings();

    // Search and book a carpool
    void searchAndBookCarpool(User& user);

    // Unlist a carpool
    bool unlistCarpool(User& user);
};

#endif // CARPOOL_MANAGER_H
