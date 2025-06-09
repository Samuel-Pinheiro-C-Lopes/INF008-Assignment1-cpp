#include "external_participant.h"

#include"participant.h"

#include<iostream>
#include<string>

/* Default id sequence */
int ExternalParticipant::currentId = 0;
int ExternalParticipant::nextId() {
    return ExternalParticipant::currentId++;
}

void ExternalParticipant::printSelf() const {
    std::cout << "External name: ";
    Participant::printSelf();
    std::cout << "Came from " << this->originUniversity << " university." << std::endl;
}

std::string ExternalParticipant::originUniversityFromInput() {
    std::string originUniversity;
    std::cin >> originUniversity;
    return originUniversity;
}
