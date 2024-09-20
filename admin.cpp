#include "Admin.h"
bool Admin::AdminVerification(const string& inputPassword) {
    return inputPassword == "creepypastaAAA"; //checking if password is correct or not
}
bool Admin::isAdmin(const string& inputPassword) const{
    return authenticate(inputPassword); // Check if the password matches
};
