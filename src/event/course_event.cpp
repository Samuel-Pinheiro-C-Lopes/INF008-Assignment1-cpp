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
    Prompt::printPartialSeparator();
    this->professor->printSelf();
    Prompt::printPartialSeparator();
    std::cout << "Course subject: " << std::endl;
    this->subject->printSelf();
}

bool CourseEvent::addTutorRegistration(const std::shared_ptr<Registration<StudentParticipant>>& tutorRegistration) {
    return Event<StudentParticipant>::addRegistrationTo<Registration<StudentParticipant>>(this->tutorsRegistrations, tutorRegistration);
}

std::vector<int> CourseEvent::getTutorsKeys() {
    return Event<StudentParticipant>::getParticipantsKeysFrom(this->tutorsRegistrations);
}

/*
CourseEvent::CourseEvent(std::string name, int vacancies, std::string date, const std::shared_ptr<ProfessorParticipant>& professor, const std::shared_ptr<Subject>& subject) : Event(nextId(), name, vacancies, date), professor(CourseEvent::validateProfessor(professor, subject) ? professor : nullptr ), subject(subject) {
    if (this->professor == nullptr) {
        std::cout << "The professor provided wasn't valid for the course event." << std::endl;
        professor->printSelf();
    }
};
*/

/* Should only receive
 * StudentParticipants */
/*
bool CourseEvent::registerParticipant(const std::shared_ptr<StudentParticipant>& participant) {
    return Event::registerParticipant(participant);
}
*/
bool CourseEvent::validateProfessor(const std::shared_ptr<ProfessorParticipant>& professor, const std::shared_ptr<Subject>& subject, const bool verbose) {
    bool valid = professor->teaches(subject);
    if (!valid && verbose) {
        std::cout << "The professor: " << std::endl;
        professor->printSelf();
        std::cout << "Isn't valid for this couse event since he/she doesn't teaches the subject." << std::endl;
    }
    return valid;
}
