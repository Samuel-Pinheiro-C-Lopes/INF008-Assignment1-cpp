#include"lecture_event.h"

#include"event.h"
#include"professor_participant.h"
#include"subject.h"

#include<iostream>
#include<unordered_map>

/* Default id sequence */
int LectureEvent::currentId = 1;
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
    for (const std::pair<int, Ptr<Subject>>& pair : this->subjects)
        pair.second->printSelf();
    Prompt::printPartialSeparator();
}

Json LectureEvent::serializeSelf() const {
    Json json = Event<StudentParticipant>::serializeSelf();
    Json json_array = Json::array();

    for (const std::pair<int, Ptr<Subject>>& pair : this->subjects)
        json_array.push_back({
            { "subject", pair.second->getId() }
        });

    json["subjects"] = json_array;
    json["professor"] = this->professor->getId();

    return json;
}
