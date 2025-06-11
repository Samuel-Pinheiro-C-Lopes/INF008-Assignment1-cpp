#ifndef COURSE_EVENT_H
#define COURSE_EVENT_H

#include"event.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"subject.h"
#include"prompt.h"

#include"alias.h"

#include<string>
#include<memory>
#include<vector>

using namespace alias;

class CourseEvent : public Event<StudentParticipant> {
public:
    CourseEvent(
        const String& name,
        const int vacancies,
        const String& date,
        const Ptr<ProfessorParticipant>& professor,
        const Ptr<Subject>& subject
    ) : Event(nextId(), name, vacancies, date),
        professor(professor),
        subject(subject) {};

    CourseEvent(
        const Map<int, Ptr<Subject>>& availableSubjects,
        const Map<int, Ptr<ProfessorParticipant>>& availableProfessors
    ) : Event(nextId()),
        professor(Prompt::forType<ProfessorParticipant>::getSelectableFromInput("Select the professor that is going to teach this course:", availableProfessors)),
        subject(Prompt::forType<Subject>::getSelectableFromInput("Select the course subject:", availableSubjects)) {};

    bool addTutorRegistration(const Ptr<Registration<StudentParticipant>>& tutorRegistration);

    Vector<int> getTutorsKeys();

    void printSelf() const override;
    Json serializeSelf() const override;
protected:
    int nextId() override;
private:
    static constexpr bool VERBOSE = true;
    static int currentId;
    Ptr<Subject> subject;
    Ptr<ProfessorParticipant> professor;
    Map<int, Ptr<Registration<StudentParticipant>>> tutorsRegistrations;

    /* maybe that validation is better in the Professor class? Debatable... */
    /*
    static bool validateProfessor(const Ptr<ProfessorParticipant>& professor, const Ptr<Subject>& subject, const bool verbose);
    */
};

#endif
