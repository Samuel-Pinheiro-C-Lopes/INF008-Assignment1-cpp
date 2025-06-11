#include"registration.h"

#include"participant.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"external_participant.h"

#include<iostream>

template<typename T>
void Registration<T>::printSelf() const {
    RegistrationBase::printSelf();
}

template class Registration<Participant>;
template class Registration<StudentParticipant>;
template class Registration<ProfessorParticipant>;
template class Registration<ExternalParticipant>;
