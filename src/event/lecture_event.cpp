#include"lecture_event.h"

#include"event.h"
#include"professor_participant.h"
#include"subject.h"

#include<iostream>
#include<unordered_map>

/* Default id sequence */
int LectureEvent::currentId = 0;
int LectureEvent::nextId() {
    return LectureEvent::currentId++;
}

void LectureEvent::printSelf() const {
    Event<StudentParticipant>::printSelf();
    std::cout << "Professor: " << std::endl;
    Prompt::printPartialSeparator();
    this->professor->printSelf();
    Prompt::printPartialSeparator();
    std::cout << "Lecture Subjects: " << std::endl;
    Prompt::printPartialSeparator();
    for (const std::pair<int, std::shared_ptr<Subject>> pair : this->subjects)
        pair.second->printSelf();
    Prompt::printPartialSeparator();
}
