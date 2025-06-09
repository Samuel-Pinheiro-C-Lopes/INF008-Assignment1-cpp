#include"fair_event.h"
#include"event.h"
#include"participant.h"
#include"registration_base.h"

#include<iostream>
#include<unordered_map>

/* Default id sequence */
int FairEvent::currentId = 0;
int FairEvent::nextId() {
    return FairEvent::currentId++;
}

void FairEvent::printSelf() const {
    Event::printSelf();
    std::cout << "Presenters: " << std::endl;
    for (const std::pair<int, std::shared_ptr<RegistrationBase>> pair : presentersRegistrations) {
        pair.second->printSelf();
        std::cout << std::endl;
    }
}

bool FairEvent::addPresenterRegistration(const std::shared_ptr<RegistrationBase>& presenterRegistration) {
    return Event<ExternalParticipant>::addRegistrationTo<RegistrationBase>(this->presentersRegistrations, presenterRegistration);
}

/*
bool FairEvent::addPresenterRegistration(const std::shared_ptr<Participant>& presenterRegistration) {
    if (vacancies == 0) return false;
    bool wasRegistrationInserted = presentersRegistrations.insert(std::make_pair(presenterRegistration->getId(), presenterRegistration)).second;
    if (wasRegistrationInserted) vacancies--;
    return wasRegistrationInserted;
}
*/
