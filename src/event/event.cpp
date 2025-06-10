#include"event.h"
#include"event_base.h"
#include"participant.h"
#include"registration.h"
#include"external_participant.h"
#include"professor_participant.h"

#include"student_participant.h"

#include<iostream>
#include<unordered_map>
#include<memory>

/* Prints the name through super class
 * entity own printSelf() implementation
 * and then proceeds to print the
 * available vacancies, date and
 * all the participants */
template<typename AttendeeType>
void Event<AttendeeType>::printSelf() const {
    EventBase::printSelf();
    std::cout << "Attendees: " << std::endl;
    for (const std::pair<int, std::shared_ptr<Registration<AttendeeType>>> pair : this->attendeesRegistrations) {
        pair.second->printSelf();
        std::cout << std::endl;
    }
}

/* Base registration behavior.
 * Checks the availability with the
 * vacancies property and then proceeds to
 * try an insertion if the event
 * is available for new participants.
 * Returns if it was able to insert. */

/*
template<typename ParticipantType>
bool Event<ParticipantType>::registerParticipant(const std::shared_ptr<ParticipantType>& participant) {
    if (vacancies == 0) return false;
    bool wasParticipantInserted = participants.insert(std::make_pair(participant->getId(), participant)).second;
    if (wasParticipantInserted) vacancies--;
    return wasParticipantInserted;
}
*/
/* Note: unordered_map::insert([...])
 * returns a pair whose second value is
 * a boolean which value is true if it
 * did perform the insertion and false
 * otherwise */

template<typename AttendeeType>
bool Event<AttendeeType>::addAttendeeRegistration(const std::shared_ptr<Registration<AttendeeType>>& attendeeRegistration) {
    return Event<AttendeeType>::addRegistrationTo<Registration<AttendeeType>>(this->attendeesRegistrations, attendeeRegistration);
}

template<typename AttendeeType>
std::vector<int> Event<AttendeeType>::getAttendesKeys() const {
    return Event<AttendeeType>::getParticipantsKeysFrom<Registration<AttendeeType>>(this->attendeesRegistrations);
}

/* telling the compiler which types
 * will be used to avoid link errors */
template class Event<Participant>;
template class Event<StudentParticipant>;
template class Event<ExternalParticipant>;
template class Event<ProfessorParticipant>;
