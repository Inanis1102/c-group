#ifndef ADMIN_H
#define ADMIN_H
#include <string>
using namespace std;
class Admin{
public:
    Admin(const string& initialPassword);
    bool AdminVerification(const string& inputPassword) const;
    bool isAdmin(const string& inputPassword) const;
    static bool authenticate(const string &inputPassword);
private:
string password;
};

#endif // ADMIN_H
