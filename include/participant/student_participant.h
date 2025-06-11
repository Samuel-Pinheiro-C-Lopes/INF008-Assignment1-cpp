#ifndef STUDENT_PARTICIPANT_H
#define STUDENT_PARTICIPANT_H

#include"participant.h"
#include"subject.h"

#include"alias.h"

#include<memory>
#include<unordered_map>

using namespace alias;

class StudentParticipant : public Participant {
public:
    StudentParticipant(
        const Map<int, Ptr<Subject>>& availableSubjects
    ) : Participant(nextId()),
        learningSubjects(Prompt::forType<Subject>::getSelectablesFromInput("Select the subjects the student studies:", availableSubjects)) {};

    StudentParticipant(
        String name,
        String cpf,
        const Map<int, Ptr<Subject>>& learningSubjects
    ) : Participant(nextId(), name, cpf), learningSubjects(learningSubjects) {};

    void printSelf() const override;
    Json serializeSelf() const override;
    int nextId() override;
private:
    static int currentId;
    Map<int, Ptr<Subject>> learningSubjects;
};

#endif
