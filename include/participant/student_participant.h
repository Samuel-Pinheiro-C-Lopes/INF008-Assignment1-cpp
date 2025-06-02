#ifndef STUDENT_PARTICIPANT_H
#define STUDENT_PARTICIPANT_H

#include"participant.h"
#include"subject.h"

#include<memory>
#include<unordered_map>

class StudentParticipant : public Participant {
public:
    StudentParticipant(const std::unordered_map<int, std::shared_ptr<Subject>>& availableSubjects) : Participant(nextId()), learningSubjects(Prompt::forType<Subject>::getSelectablesFromInput("Select the subjects the student studies:", availableSubjects)) {};
    StudentParticipant(std::string name, std::string cpf) : Participant(nextId(), name, cpf) {};
    void printSelf() const override;
    int nextId() override;
private:
    static int currentId;
    std::unordered_map<int, std::shared_ptr<Subject>> learningSubjects;
};

#endif
