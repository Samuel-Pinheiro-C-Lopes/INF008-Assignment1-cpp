#ifndef COURSE_EVENT_H
#define COURSE_EVENT_H

#include"event.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"subject.h"
#include"prompt.h"

#include<string>
#include<memory>

class CourseEvent : public Event<StudentParticipant> {
public:
    /* I'm not quite sure overwritting the addGuestRegistration is needed since the type assertion
     * is already made using the template definition up there... */
    // bool registerGuestParticipant(const std::shared_ptr<StudentParticipant>& participant) override;
    CourseEvent(const std::string& name, const int vacancies, const std::string& date, const std::shared_ptr<ProfessorParticipant>& professor, const std::shared_ptr<Subject>& subject) : Event(nextId(), name, vacancies, date), professor(CourseEvent::validateProfessor(professor, subject, VERBOSE) ? professor : nullptr ), subject(subject) {};

    CourseEvent(const std::unordered_map<int, std::shared_ptr<Subject>>& availableSubjects, const std::unordered_map<int, std::shared_ptr<ProfessorParticipant>>& availableProfessors) : Event(nextId()), subject(Prompt::forType<Subject>::getSelectableFromInput("Select the course subject:", availableSubjects)), professor(Prompt::forType<ProfessorParticipant>::getSelectableFromInput("Select the professor that is going to teach this course:", availableProfessors)) {};
    void printSelf() const override;
protected:
    int nextId() override;
private:
    static constexpr bool VERBOSE = true;
    static int currentId;
    std::shared_ptr<Subject> subject;
    std::shared_ptr<ProfessorParticipant> professor;
    /* maybe that validation is better in the Professor class? Debatable... */
    static bool validateProfessor(const std::shared_ptr<ProfessorParticipant>& professor, const std::shared_ptr<Subject>& subject, const bool verbose);
};

#endif
