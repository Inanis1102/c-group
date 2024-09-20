#include "rating.h"
#include <iostream>

// Constructor to initialize rating system
Rating::Rating(const std::string& name, int rating, const std::string& review)
    : name(name), rating(rating), review(review) {}

// Getters
std::string Rating::getMemberName() const {
    return name;
}

int Rating::getRating() const {
    return rating;
}

std::string Rating::getReview() const {
    return review;
}

// Setters
void Rating::setMemberName(const std::string& personName) {
    this->name = personName;
}

void Rating::setRating(int rating) {
    this->rating = rating;
}

void Rating::setReview(const std::string& review) {
    this->review = review;
}

// Function to display rating details
void Rating::displayRating() const {
    std::cout << "Person Name: " << name << "\n";
    std::cout << "Rating: " << rating << " stars\n";
    std::cout << "Review: " << review << "\n";
}
