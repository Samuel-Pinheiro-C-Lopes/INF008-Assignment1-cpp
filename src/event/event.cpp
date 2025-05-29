#include"event.h"
#include"entity.h"
#include"participant.h"

#include<iostream>
#include<unordered_map>

void Event::printSelf() const {
    Entity::printSelf();
    std::cout << "Vacancies: " << vacancies << "." << std::endl;
    std::cout << "Participants: " << std::endl;
    for (const std::pair<int, std::shared_ptr<Participant>>& pair : participants)
        pair.second->printSelf();
}

bool Event::registerParticipant(std::shared_ptr<Participant> participant) {
    return participants.insert({participant->getId(), participant}).second; // seconds is a boolean, true if it did insert (there wasn't already a value with said key)
    // The bellow subscript operator seems elegant
    // participants[participant->getId()] = participant;
}
