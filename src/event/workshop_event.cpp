#include"workshop_event.h"

#include"event.h"
#include"professor_participant.h"

#include<iostream>
#include<vector>

/* Default id sequence */
int WorkshopEvent::currentId = 0;
int WorkshopEvent::nextId() {
    return WorkshopEvent::currentId++;
}

void WorkshopEvent::printSelf() const {
    Event<StudentParticipant>::printSelf();
    this->subject->printSelf();
    std::cout << "Professors: " << std::endl;
    for (const std::pair<int, std::shared_ptr<ProfessorParticipant>> pair : this->professors) {
        pair.second->printSelf();
        std::cout << std::endl;
    }
    std::cout << "Guests: " << std::endl;
    for (const std::pair<int, std::shared_ptr<Registration<ExternalParticipant>>> pair : this->guestsRegistrations) {
        pair.second->printSelf();
        std::cout << std::endl;
    }
}

bool WorkshopEvent::addGuestRegistration(const std::shared_ptr<Registration<ExternalParticipant>>& guestRegistration) {
        return Event<StudentParticipant>::addRegistrationTo<Registration<ExternalParticipant>>(this->guestsRegistrations, guestRegistration);
}

std::vector<int> WorkshopEvent::getGuestsKeys() const {
    return Event<StudentParticipant>::getParticipantsKeysFrom
        <Registration<ExternalParticipant>>(this->guestsRegistrations);
}
