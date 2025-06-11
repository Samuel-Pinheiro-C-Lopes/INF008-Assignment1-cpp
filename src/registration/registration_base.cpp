#include"registration_base.h"

#include"entity.h"

#include<iostream>

void RegistrationBase::printSelf() const {
    std::cout << "Registration date:" << this->date.getValue() << "." << std::endl;

    Prompt::printPartialSeparator();
    std::cout << "Participant: " << std::endl;
    this->participant->printSelf();
    Prompt::printPartialSeparator();
}

int RegistrationBase::getParticipantId() const {
    return this->participant->getId();
}
