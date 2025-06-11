#include"course_event.h"

#include"event.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"subject.h"

#include<memory>
#include<iostream>

/* Default id sequence */
int CourseEvent::currentId = 1;
int CourseEvent::nextId() {
    return CourseEvent::currentId++;
}

void CourseEvent::printSelf() const {
    Event::printSelf();
    std::cout << "│"<< "Professor: " << std::endl;
    if (this->professor)
        this->professor->printSelf();
    else std::cout << "[NOT ASSIGNED]" << std::endl;
    std::cout << "│"<< "Course subject: " << std::endl;
    this->subject->printSelf();
}

bool CourseEvent::addTutorRegistration(
    const Ptr<Registration<StudentParticipant>>& tutorRegistration
) {
    return Event<StudentParticipant>::addRegistrationTo<Registration<StudentParticipant>>(this->tutorsRegistrations, tutorRegistration);
}

std::vector<int> CourseEvent::getTutorsKeys() {
    return Event<StudentParticipant>::getParticipantsKeysFrom(this->tutorsRegistrations);
}

Json CourseEvent::serializeSelf() const {
    Json json = Event<StudentParticipant>::serializeSelf();

    json["professor"] = this->professor->getId();
    json["subject"] = this->subject->getId();

    return json;
}
