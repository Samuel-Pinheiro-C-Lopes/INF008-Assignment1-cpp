#include "external_participant.h"

#include"participant.h"

#include<iostream>
#include<string>

/* Default id sequence */
int ExternalParticipant::currentId = 1;
int ExternalParticipant::nextId() {
    return ExternalParticipant::currentId++;
}

void ExternalParticipant::printSelf() const {
    std::cout << "External name: ";
    Participant::printSelf();
    std::cout << "Came from " << this->originUniversity << " university." << std::endl;
}

Json ExternalParticipant::serializeSelf() const {
    Json json = Participant::serializeSelf();

    json["origin university"] = this->originUniversity;

    return json;
}
