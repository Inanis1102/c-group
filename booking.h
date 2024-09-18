#ifndef BOOKING_H
#define BOOKING_H

#include <string>

// Forward declare Carpool class to avoid circular dependency
class Carpool;

class Booking {
private:
    std::string passengerUsername;
    Carpool* bookedCarpool; // Pointer to the booked carpool
    bool isAccepted;

public:
    // Constructor
    Booking(const std::string& passengerUsername, Carpool* carpool);

    // Accept or reject the booking
    void acceptBooking();
    void cancelBooking();

    // Display booking details
    void displayBookingDetails() const;
};

#endif // BOOKING_H
