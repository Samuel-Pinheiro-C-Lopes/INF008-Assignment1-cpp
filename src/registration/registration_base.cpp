#include"registration_base.h"

#include"entity.h"

#include<iostream>

void RegistrationBase::printSelf() const {
    std::cout << "Registration date:" << this->date.getValue() << "." << std::endl;
}
