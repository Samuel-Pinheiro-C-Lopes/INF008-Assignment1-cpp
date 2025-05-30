#ifndef COURSE_EVENT_H
#define COURSE_EVENT_H

#include"event.h"
#include"student_participant.h"

#include<string>
#include<memory>

class CourseEvent : public Event<StudentParticipant> {
public:
    bool registerParticipant(std::shared_ptr<StudentParticipant> participant) override;
    CourseEvent(std::string name, int vacancies, std::string date) : Event(nextId(), name, vacancies, date) { };
protected:
    int nextId() override;
private:
    static int currentId;
};

#endif
