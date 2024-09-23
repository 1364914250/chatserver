#ifndef GROUPUSER_H
#define GROUPUSER_H
#include "user.hpp"
#include <string>
//继承默认是私有继承，记得声明是公共继承
class GroupUser : public User
{

public:
    void setRole(string role) { this->role = role; }
    string getRole() { return this->role; }

private:
    string role;
};
#endif