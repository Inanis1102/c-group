#include "booking.h"
#include "carpool.h"
#include <iostream>

// Constructor
Booking::Booking(const std::string& passengerUsername, Carpool* carpool) 
    : passengerUsername(passengerUsername), bookedCarpool(carpool), isAccepted(false) {}

// Accept the booking
void Booking::acceptBooking() {
    if (bookedCarpool->getAvailableSeats() > 0){
        isAccepted = true;
        bookedCarpool->setAvailableSeats(bookedCarpool->getAvailableSeats() - 1); //reduce available seats
        std::cout << "Booking accepted.\n";
    } else {
        std::cout << "Booking cannot be acepted. No available seats.\n";
    }
}

// Cancel the booking (if not yet accepted)
void Booking::cancelBooking() {
    if (!isAccepted) {
        std::cout << "Booking canceled successfully.\n";
        bookedCarpool->setAvailableSeats(bookedCarpool->getAvailableSeats() + 1);  // Return the seat to the carpool
    } else {
        std::cout << "Booking cannot be canceled after being accepted.\n";
    }
}

// Display booking details
void Booking::displayBookingDetails() const {
    std::cout << "\nBooking Details:\n";
    std::cout << "Passenger Username: " << passengerUsername << "\n";
    bookedCarpool->displayCarpoolDetails();  // Display carpool details
    std::cout << "Booking Status: " << (isAccepted ? "Accepted" : "Pending") << "\n";
}
