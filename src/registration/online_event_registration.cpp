#include"online_event_registration.h"
#include"registration.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"external_participant.h"

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

template class OnlineEventRegistration<Participant>;
template class OnlineEventRegistration<StudentParticipant>;
template class OnlineEventRegistration<ProfessorParticipant>;
template class OnlineEventRegistration<ExternalParticipant>;
