#ifndef COURSE_EVENT_H
#define COURSE_EVENT_H

#include"event.h"
#include"student_participant.h"
#include"professor_participant.h"

#include<string>
#include<memory>

class CourseEvent : public Event<StudentParticipant> {
public:
    bool registerParticipant(StudentParticipant* participant) override;
    CourseEvent(std::string name, int vacancies, std::string date, ProfessorParticipant* professor, Subject* subject);
    void printSelf() const override;
protected:
    int nextId() override;
private:
    static int currentId;
    Subject* subject;
    ProfessorParticipant* professor;
    static bool validateProfessor(ProfessorParticipant* professor, Subject* subject);
};

#endif
