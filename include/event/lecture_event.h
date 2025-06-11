#ifndef LECTURE_EVENT_H
#define LECTURE_EVENT_H

#include"event.h"
#include"subject.h"
#include"professor_participant.h"
#include"participant.h"
#include"student_participant.h"

#include"alias.h"

#include<memory>
#include<string>
#include<unordered_map>

using namespace alias;

class LectureEvent : public Event<StudentParticipant> {
public:
    LectureEvent(
        const Map<int, Ptr<Subject>>& availableSubjects,
        const Map<int, Ptr<ProfessorParticipant>>& availableProfessors
    ) : Event(nextId()),
        subjects(Prompt::forType<Subject>::getSelectablesFromInput("Select the subject for the lecture event:", availableSubjects)),
        professor(Prompt::forType<ProfessorParticipant>::getSelectableFromInput("Select the professor for the lecture event:", availableProfessors)) {};

    LectureEvent(
        const String& name,
        const int vacancies,
        const String& date,
        const Map<int, Ptr<Subject>>& subjects,
        const Ptr<ProfessorParticipant>& professor
    ) : Event(nextId(), name, vacancies, date), subjects(subjects), professor(professor) {};

    void printSelf() const override;
    Json serializeSelf() const override;
private:
    static int currentId;
    int nextId() override;
    Map<int, Ptr<Subject>> subjects;
    Ptr<ProfessorParticipant> professor;
};

#endif
