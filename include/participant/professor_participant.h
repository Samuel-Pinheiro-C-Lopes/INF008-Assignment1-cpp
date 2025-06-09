#ifndef PROFESSOR_PARTICIPANT_H
#define PROFESSOR_PARTICIPANT_H

#include"participant.h"
#include"subject.h"

#include<unordered_map>
#include<memory>

class ProfessorParticipant : public Participant {
public:
    ProfessorParticipant(const std::unordered_map<int, std::shared_ptr<Subject>>& availableSubjects) : Participant(nextId()), teachingSubjects(Prompt::forType<Subject>::getSelectablesFromInput("Select the subjects the professor teaches:", availableSubjects)) {};

    ProfessorParticipant(std::string name, std::string cpf, const std::unordered_map<int, std::shared_ptr<Subject>>& teachingSubjects) : Participant(nextId(), name, cpf),  teachingSubjects(teachingSubjects) {};

    void printSelf() const override;
    bool teaches(const std::shared_ptr<Subject>& subject) const;
    bool addSubject(const std::shared_ptr<Subject>& subject);
private:
    int nextId() override;
    static int currentId;
    std::unordered_map<int, std::shared_ptr<Subject>> teachingSubjects;
};

#endif
