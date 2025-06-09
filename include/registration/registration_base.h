#ifndef REGISTRATION_BASE_H
#define REGISTRATION_BASE_H

#include"entity.h"
#include"date.h"

#include<string>

class RegistrationBase : public Entity {
public:
    void printSelf() const override;
protected:
    RegistrationBase(int id) : Entity(id), date() {};
    RegistrationBase(int id, const std::string& date) : Entity(id), date(date) {};
private:
    Date date;
};

#endif
