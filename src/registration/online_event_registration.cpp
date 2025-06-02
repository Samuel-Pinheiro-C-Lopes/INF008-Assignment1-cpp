#include"online_event_registration.h"
#include"registration.h"
#include"student_participant.h"

#include<iostream>

template<typename ParticipantType>
int OnlineEventRegistration<ParticipantType>::currentId = 0;

template<typename ParticipantType>
int OnlineEventRegistration<ParticipantType>::nextId() {
    return OnlineEventRegistration<ParticipantType>::currentId++;
};

template<typename ParticipantType>
void OnlineEventRegistration<ParticipantType>::printSelf() const {
    Registration<ParticipantType>::printSelf();
    std::cout << "E-mail for contact: " << this->contactEmail << "." << std::endl;
};

template class Registration<Participant>;
template class Registration<StudentParticipant>;
