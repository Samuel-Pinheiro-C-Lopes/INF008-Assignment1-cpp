#include"student_participant.h"

#include"participant.h"
#include"prompt.h"

#include<iostream>

/* Default id sequence */
int StudentParticipant::currentId = 0;
int StudentParticipant::nextId() {
    return StudentParticipant::currentId++;
}

void StudentParticipant::printSelf() const {
    std::cout << "Student name: ";
    Participant::printSelf();
    std::cout << "Currently learning the following subjects: " << std::endl;
    for (const std::pair<int, std::shared_ptr<Subject>>& pair : this->learningSubjects)
        pair.second->printSelf();
}
