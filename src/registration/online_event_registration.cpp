#include"online_event_registration.h"
#include"registration.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"external_participant.h"

#include<iostream>

template<typename T>
int OnlineEventRegistration<T>::currentId = 1;

template<typename T>
int OnlineEventRegistration<T>::nextId() {
    return OnlineEventRegistration<T>::currentId++;
};

template<typename T>
void OnlineEventRegistration<T>::printSelf() const {
    Registration<T>::printSelf();
    std::cout << "│"<< "E-mail for contact: " << this->contactEmail << "." << std::endl;
};

template class OnlineEventRegistration<Participant>;
template class OnlineEventRegistration<StudentParticipant>;
template class OnlineEventRegistration<ProfessorParticipant>;
template class OnlineEventRegistration<ExternalParticipant>;
