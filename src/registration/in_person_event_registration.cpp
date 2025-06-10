#include"in_person_event_registration.h"
#include"registration.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"external_participant.h"

#include<iostream>

template<typename ParticipantType>
int InPersonEventRegistration<ParticipantType>::currentId = 0;

template<typename ParticipantType>
int InPersonEventRegistration<ParticipantType>::nextId() {
    return InPersonEventRegistration<ParticipantType>::currentId++;
};

template<typename ParticipantType>
void InPersonEventRegistration<ParticipantType>::printSelf() const {
    Registration<ParticipantType>::printSelf();
    std::cout << "Needs accessibility: ";
    if (this->accessibility) std::cout << "[YES]." << std::endl;
    else std::cout << "[NO]" << std::endl;
};

template class InPersonEventRegistration<Participant>;
template class InPersonEventRegistration<StudentParticipant>;
template class InPersonEventRegistration<ProfessorParticipant>;
template class InPersonEventRegistration<ExternalParticipant>;

