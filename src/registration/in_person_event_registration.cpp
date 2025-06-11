#include"in_person_event_registration.h"
#include"registration.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"external_participant.h"

#include<iostream>

template<typename T>
int InPersonEventRegistration<T>::currentId = 1;

template<typename T>
int InPersonEventRegistration<T>::nextId() {
    return InPersonEventRegistration<T>::currentId++;
};

template<typename T>
void InPersonEventRegistration<T>::printSelf() const {
    Registration<T>::printSelf();

    std::cout << "│" << "Needs accessibility: ";
    if (this->accessibility) std::cout << "[YES]." << std::endl;
    else std::cout << "[NO]" << std::endl;
};

template class InPersonEventRegistration<Participant>;
template class InPersonEventRegistration<StudentParticipant>;
template class InPersonEventRegistration<ProfessorParticipant>;
template class InPersonEventRegistration<ExternalParticipant>;

