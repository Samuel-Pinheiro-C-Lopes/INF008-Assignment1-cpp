#include"workshop_event.h"

#include"event.h"
#include"professor_participant.h"

#include<iostream>
#include<vector>

/* Default id sequence */
int WorkshopEvent::currentId = 1;
int WorkshopEvent::nextId() {
    return WorkshopEvent::currentId++;
}

void WorkshopEvent::printSelf() const {
    Event<StudentParticipant>::printSelf();
    this->subject->printSelf();

    std::cout << "Professors: " << std::endl;
    for (const std::pair<int, Ptr<ProfessorParticipant>> pair : this->professors) {
        pair.second->printSelf();
        std::cout << std::endl;
    }

    std::cout << "Guests: " << std::endl;
    for (const std::pair<int, Ptr<Registration<ExternalParticipant>>> pair : this->guestsRegistrations) {
        pair.second->printSelf();
        std::cout << std::endl;
    }
}

bool WorkshopEvent::addGuestRegistration(const Ptr<Registration<ExternalParticipant>>& guestRegistration) {
        return Event<StudentParticipant>::addRegistrationTo<Registration<ExternalParticipant>>(this->guestsRegistrations, guestRegistration);
}

Vector<int> WorkshopEvent::getGuestsKeys() const {
    return Event<StudentParticipant>::getParticipantsKeysFrom
        <Registration<ExternalParticipant>>(this->guestsRegistrations);
}


Json WorkshopEvent::serializeSelf() const {
    Json json = Event<StudentParticipant>::serializeSelf();
    Json json_pparray = Json::array();
    Json json_eparray = Json::array();

    for (const std::pair<int, Ptr<ProfessorParticipant>>& pair : this->professors) {
        json_pparray.push_back({
            { "professor", pair.second->getId() }
        });
    }

    for (const std::pair<int, Ptr<Registration<ExternalParticipant>>>& pair : this->guestsRegistrations) {
        json_eparray.push_back({
            { "registration", pair.first },
            { "external", pair.second->getParticipantId() }
        });
    }

    json["professors"] = json_pparray;
    json["guests"] = json_eparray;
    json["subject"] = this->subject->getId();

    return json;
}
