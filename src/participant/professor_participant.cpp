#include"professor_participant.h"

#include"subject.h"
#include<unordered_map>
#include<iostream>

/* Default id sequence */
int ProfessorParticipant::currentId = 0;
int ProfessorParticipant::nextId() {
    return ProfessorParticipant::currentId++;
}

void ProfessorParticipant::printSelf() const {
    Participant::printSelf();
    std::cout << "Subjects: " << std::endl;
    for (const std::pair<int, Subject*> pair : this->subjects)
        pair.second->printSelf();
}

bool ProfessorParticipant::teaches(Subject* subject) const {
    return this->subjects.find(subject->getId()) != this->subjects.end();
}

bool ProfessorParticipant::addSubject(Subject* subject) {
    return this->subjects.insert(std::make_pair(subject->getId(), subject)).second;
}
