#include"registration.h"

#include"registration_base.h"
#include"participant.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"external_participant.h"

#include<iostream>

template<typename ParticipantType>
void Registration<ParticipantType>::printSelf() const {
    RegistrationBase::printSelf();
    Prompt::printPartialSeparator();
    std::cout << "Participant: " << std::endl;
    this->participant->printSelf();
    Prompt::printPartialSeparator();
}

template class Registration<Participant>;
template class Registration<StudentParticipant>;
template class Registration<ProfessorParticipant>;
template class Registration<ExternalParticipant>;
