#ifndef PROFESSOR_PARTICIPANT_H
#define PROFESSOR_PARTICIPANT_H

#include"participant.h"
#include"subject.h"

#include"alias.h"

#include<unordered_map>
#include<memory>

using namespace alias;

class ProfessorParticipant : public Participant {
public:
    ProfessorParticipant(
        const Map<int, Ptr<Subject>>& availableSubjects
    ) : Participant(nextId()),
        teachingSubjects(Prompt::forType<Subject>::getSelectablesFromInput("Select the subjects the professor teaches:", availableSubjects)) {};

    ProfessorParticipant(
        String name,
        String cpf,
        const Map<int, Ptr<Subject>>& teachingSubjects
    ) : Participant(nextId(), name, cpf),  teachingSubjects(teachingSubjects) {};

    void printSelf() const override;
    Json serializeSelf() const override;
    bool teaches(const Ptr<Subject>& subject) const;
    bool addSubject(const Ptr<Subject>& subject);
private:
    int nextId() override;
    static int currentId;
    Map<int, Ptr<Subject>> teachingSubjects;
};

#endif
