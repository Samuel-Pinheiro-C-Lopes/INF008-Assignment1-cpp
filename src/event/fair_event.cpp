#include"fair_event.h"

#include"event.h"
#include"participant.h"
#include"external_participant.h"
#include"registration_base.h"

#include<iostream>
#include<unordered_map>
#include<vector>

/* Default id sequence */
int FairEvent::currentId = 1;
int FairEvent::nextId() {
    return FairEvent::currentId++;
}

void FairEvent::printSelf() const {
    Event::printSelf();
    std::cout << "│" << "Presenters: " << std::endl;
    for (const std::pair<const int, Ptr<Registration<StudentParticipant>>>& pair : presentersRegistrations) {
        pair.second->printSelf();
        std::cout << std::endl;
    }
}

bool FairEvent::addPresenterRegistration(
    const Ptr<Registration<StudentParticipant>>& presenterRegistration
) {
    return Event<ExternalParticipant>::addRegistrationTo<Registration<StudentParticipant>>(this->presentersRegistrations, presenterRegistration);
}

Vector<int> FairEvent::getPresentersKeys() const {
    return Event<ExternalParticipant>::getParticipantsKeysFrom
        <Registration<StudentParticipant>>(this->presentersRegistrations);
}

Json FairEvent::serializeSelf() const {
    Json json = Event<ExternalParticipant>::serializeSelf();
    Json json_sparray = Json::array();
    Json json_sarray = Json::array();

    for (const std::pair<const int, Ptr<Registration<StudentParticipant>>>& pair : this->presentersRegistrations)
        json_sparray.push_back({
            { "registration", pair.first },
            { "student", pair.second->getParticipantId() }
        });

    for (const std::pair<const int, Ptr<Subject>>& pair : this->subjects)
        json_sarray.push_back({
            { "subject", pair.second->getId() }
        });

    json["presenters"] = json_sparray;
    json["subjects"] = json_sarray;

    return json;
}
