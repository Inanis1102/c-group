#ifndef CARPOOL_H
#define CARPOOL_H

#include <string>

class Carpool {
public:
    std::string driverUsername;
    std::string departureLocation;
    std::string destinationLocation;
    std::string departureTime;
    std::string date;
    std::string vehicleModel;
    std::string vehicleColor;
    std::string vehiclePlate;
    int availableSeats;
    int contributionPerPassenger;

    Carpool(std::string driver, std::string depLoc, std::string destLoc, 
            std::string depTime, std::string dt, std::string vModel, 
            std::string vColor, std::string vPlate, int seats, int contribution);
    // Other member functions as needed
};

#endif
