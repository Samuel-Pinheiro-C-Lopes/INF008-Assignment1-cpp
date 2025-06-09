#ifndef LECTURE_EVENT_H
#define LECTURE_EVENT_H

#include"event.h"
#include"subject.h"
#include"professor_participant.h"
#include"participant.h"
#include"student_participant.h"

#include<memory>
#include<string>
#include<unordered_map>

class LectureEvent : public Event<StudentParticipant> {
public:
    LectureEvent(std::unordered_map<int, std::shared_ptr<Subject>>& availableSubjects, const std::unordered_map<int, std::shared_ptr<ProfessorParticipant>>& availableProfessors) : Event(nextId()), subjects(Prompt::forType<Subject>::getSelectablesFromInput("Select the subject for the lecture event:", availableSubjects)), professor(Prompt::forType<ProfessorParticipant>::getSelectableFromInput("Select the professor for the lecture event:", availableProfessors)) {};

    LectureEvent(const std::string& name, const int vacancies, const std::string& date, const std::unordered_map<int, std::shared_ptr<Subject>>& subjects, const std::shared_ptr<ProfessorParticipant>& professor) : Event(nextId(), name, vacancies, date), subjects(subjects), professor(professor) {};

    void printSelf() const override;
private:
    static int currentId;
    int nextId() override;
    std::unordered_map<int, std::shared_ptr<Subject>> subjects;
    std::shared_ptr<ProfessorParticipant> professor;

};

#endif
