#ifndef CURRENTUSER_H
#define CURRENTUSER_H

#include <string>
using namespace std;

class CurrentUser {
private:
    string id;
    string username;
    string password;
    string fullname;
    string role;


public:

    CurrentUser(const string id = "", const string username = "", const string password = "", const string fullname = "", const string role = "");
    
    string getId() const;
    string getUsername() const;
    string getPassword() const;
    string getFullname() const;
    string getRole() const;

};
    CurrentUser::CurrentUser(const string id, const string username, const string password, const string fullname, const string role)
    : id(id), username(username), password(password), fullname(fullname), role(role) {}

    string CurrentUser::getId() const {
        return id;
    }

    string CurrentUser::getUsername() const {
        return username;
    }

    string CurrentUser::getPassword() const {
        return password;
    }

    string CurrentUser::getFullname() const {
        return fullname;
    }

    string CurrentUser::getRole() const {
        return role;
    }

#endif