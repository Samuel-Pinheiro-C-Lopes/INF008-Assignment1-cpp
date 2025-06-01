#ifndef COURSE_EVENT_H
#define COURSE_EVENT_H

#include"event.h"
#include"student_participant.h"
#include"professor_participant.h"

#include<string>
#include<memory>

class CourseEvent : public Event<StudentParticipant> {
public:
    bool registerParticipant(const std::shared_ptr<StudentParticipant>& participant) override;
    CourseEvent(std::string name, int vacancies, std::string date, const std::shared_ptr<ProfessorParticipant>& professor, const std::shared_ptr<Subject>& subject);
    void printSelf() const override;
protected:
    int nextId() override;
private:
    static int currentId;
    std::shared_ptr<Subject> subject;
    std::shared_ptr<ProfessorParticipant> professor;
    static bool validateProfessor(const std::shared_ptr<ProfessorParticipant>& professor, const std::shared_ptr<Subject>& subject);
};

#endif
