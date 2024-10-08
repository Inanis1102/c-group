#ifndef RATING_SYSTEM_H
#define RATING_SYSTEM_H

#include <string>

class Rating {
private:
    std::string name; // Name of passenger or driver (The one being rated)
    int rating;             // Rating
    std::string review;      // Review

public:
    // Constructor
    Rating(const std::string& name, int rating, const std::string& review);

    // Getter
    std::string getMemberName() const;
    int getRating() const;
    std::string getReview() const;

    // Setter
    void setMemberName(const std::string& name);
    void setRating(int rating);
    void setReview(const std::string& review);

    // Display rating detail
    void displayRating() const;
};

#endif
