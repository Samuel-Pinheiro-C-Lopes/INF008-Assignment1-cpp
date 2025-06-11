#include"registration_base.h"

#include"entity.h"

#include<iostream>

void RegistrationBase::printSelf() const {
    std::cout << "│"<< "Registration date:" << this->date.getValue() << "." << std::endl;
    std::cout << "│" << std::endl;
    std::cout << "│"<< "Participant: " << std::endl;
    this->participant->printSelf();
    std::cout << "│" << std::endl;
}

int RegistrationBase::getParticipantId() const {
    return this->participant->getId();
}
