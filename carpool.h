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

    // Preload carpool from text
     void preloadCarpool(const std::string& driverUsername, const std::string& departure, const std::string& destination,
                        const std::string& date, const std::string& model, const std::string& color, const std::string& plate, 
                        int seats, int contribution);

    // Add a booking
    bool addBooking(const std::string& passengerUsername);

    // Getters
    std::string getDriverUsername() const { return driverUsername; }
    std::string getDepartureLocation() const { return departureLocation; }
    std::string getDestinationLocation() const { return destinationLocation; }
    std::string getDate() const { return date; }
    std::string getVehicleModel() const { return vehicleModel; }
    std::string getVehicleColor() const { return vehicleColor; }
    std::string getVehiclePlateNumber() const { return vehiclePlateNumber; }
    int getAvailableSeats() const { return availableSeats; }
    int getContributionAmount() const { return contributionAmount; }

    // Setters
    void setDriverUsername(const std::string& username) { driverUsername = username; }
    void setDepartureLocation(const std::string& departure) { departureLocation = departure; }
    void setDestinationLocation(const std::string& destination) { destinationLocation = destination; }
    void setDate(const std::string& carpoolDate) { date = carpoolDate; }
    void setVehicleModel(const std::string& model) { vehicleModel = model; }
    void setVehicleColor(const std::string& color) { vehicleColor = color; }
    void setVehiclePlateNumber(const std::string& plateNumber) { vehiclePlateNumber = plateNumber; }
    void setAvailableSeats(int seats) { availableSeats = seats; }
    void setContributionAmount(int amount) { contributionAmount = amount; }
};

#endif // CARPOOL_H
