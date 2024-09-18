#ifndef CARPOOL_H
#define CARPOOL_H

#include <string>
#include <vector>
#include "booking.h"

class Carpool {
private:
    std::string driverUsername;
    std::string departureLocation;
    std::string destinationLocation;
    std::string date;
    std::string vehicleModel;
    std::string vehicleColor;
    std::string vehiclePlateNumber;
    int availableSeats;
    int contributionAmount;

public:
    std::vector<Booking*> bookings;  // Store bookings

    // Constructor
    Carpool();

    // Create a new carpool listing
    void createCarpool(const std::string& driverUsername);

    // Display the details of the carpool listing
    void displayCarpoolDetails() const;

    // Add a booking
    bool addBooking(const std::string& passengerUsername);

    // Getters
    std::string getDriverUsername() const { return driverUsername; }
    std::string getDepartureLocation() const { return departureLocation; }
    std::string getDestinationLocation() const { return destinationLocation; }
    std::string getDate() const { return date; }
    int getAvailableSeats() const { return availableSeats; }

    // Setters
    void setAvailableSeats(int seats) { availableSeats = seats; }
};

#endif // CARPOOL_H
