#include"course_event.h"

#include"event.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"subject.h"

#include<memory>
#include<iostream>

/* Default id sequence */
int CourseEvent::currentId = 0;
int CourseEvent::nextId() {
    return CourseEvent::currentId++;
}

void CourseEvent::printSelf() const {
    Event::printSelf();
    std::cout << "Professor: " << std::endl;
    this->professor->printSelf();
    std::cout << "Subject: " << std::endl;
    this->subject->printSelf();
}

CourseEvent::CourseEvent(std::string name, int vacancies, std::string date, const std::shared_ptr<ProfessorParticipant>& professor, const std::shared_ptr<Subject>& subject) : Event(nextId(), name, vacancies, date), professor(CourseEvent::validateProfessor(professor, subject) ? professor : nullptr ), subject(subject) {
    if (this->professor == nullptr) {
        std::cout << "The professor provided wasn't valid for the course event." << std::endl;
        professor->printSelf();
    }
};

/* Should only receive
 * StudentParticipants */
bool CourseEvent::registerParticipant(const std::shared_ptr<StudentParticipant>& participant) {
    return Event::registerParticipant(participant);
}

bool CourseEvent::validateProfessor(const std::shared_ptr<ProfessorParticipant>& professor, const std::shared_ptr<Subject>& subject) {
    return professor->teaches(subject);
}
