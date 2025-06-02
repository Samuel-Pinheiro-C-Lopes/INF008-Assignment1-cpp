#include"registration.h"
#include"participant.h"
#include"student_participant.h"

#include<iostream>

template<typename ParticipantType>
void Registration<ParticipantType>::printSelf() const {
    std::cout << "Participant: " << std::endl;
    this->participant->printSelf();
    std::cout << "Registered in: " << this->date << "." << std::endl;
}

template class Registration<Participant>;
template class Registration<StudentParticipant>;
