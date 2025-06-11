#include"event.h"
#include"external_participant.h"
#include"professor_participant.h"

#include"student_participant.h"

#include<iostream>

template<typename T>
void Event<T>::printSelf() const {
    EventBase::printSelf();
    std::cout << "│" << "Attendees: " << std::endl;
    for (const std::pair<int, std::shared_ptr<Registration<T>>>& pair : this->attendeesRegistrations) {
        pair.second->printSelf();
        std::cout << "│" << std::endl;
    }
}

template<typename T>
bool Event<T>::addAttendeeRegistration(
    const Ptr<Registration<T>>& attendeeRegistration
) {
    return Event<T>::addRegistrationTo<Registration<T>>(this->attendeesRegistrations, attendeeRegistration);
}

template<typename T>
std::vector<int> Event<T>::getAttendesKeys() const {
    return Event<T>::getParticipantsKeysFrom<Registration<T>>(this->attendeesRegistrations);
}

template<typename T>
Json Event<T>::serializeSelf() const {
    Json json = EventBase::serializeSelf();
    Json j_array = Json::array();

    for (const std::pair<int, std::shared_ptr<Registration<T>>>& pair : this->attendeesRegistrations) {
        j_array.push_back({
            { "registration", pair.first },
            { "attende", pair.second->getParticipantId() }
        });
    }

    json["attendees"] = j_array;

    return json;

}

/* telling the compiler which types
 * will be used to avoid link errors */
template class Event<Participant>;
template class Event<StudentParticipant>;
template class Event<ExternalParticipant>;
template class Event<ProfessorParticipant>;
