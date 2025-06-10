#include"fair_event.h"

#include"event.h"
#include"participant.h"
#include"external_participant.h"
#include"registration_base.h"

#include<iostream>
#include<unordered_map>
#include<vector>

/* Default id sequence */
int FairEvent::currentId = 0;
int FairEvent::nextId() {
    return FairEvent::currentId++;
}

void FairEvent::printSelf() const {
    Event::printSelf();
    std::cout << "Presenters: " << std::endl;
    for (const std::pair<const int, std::shared_ptr<Registration<StudentParticipant>>>& pair : presentersRegistrations) {
        pair.second->printSelf();
        std::cout << std::endl;
    }
}

bool FairEvent::addPresenterRegistration(const std::shared_ptr<Registration<StudentParticipant>>& presenterRegistration) {
    return Event<ExternalParticipant>::addRegistrationTo<Registration<StudentParticipant>>(this->presentersRegistrations, presenterRegistration);
}

std::vector<int> FairEvent::getPresentersKeys() const {
    return Event<ExternalParticipant>::getParticipantsKeysFrom
        <Registration<StudentParticipant>>(this->presentersRegistrations);
}

/*
bool FairEvent::addPresenterRegistration(const std::shared_ptr<Participant>& presenterRegistration) {
    if (vacancies == 0) return false;
    bool wasRegistrationInserted = presentersRegistrations.insert(std::make_pair(presenterRegistration->getId(), presenterRegistration)).second;
    if (wasRegistrationInserted) vacancies--;
    return wasRegistrationInserted;
}
*/
