#ifndef PROFESSOR_PARTICIPANT_H
#define PROFESSOR_PARTICIPANT_H

#include"participant.h"
#include"subject.h"

#include<unordered_map>
#include<memory>

class ProfessorParticipant : public Participant {
public:
    void printSelf() const override;
    bool teaches(const std::shared_ptr<Subject>& subject) const;
    bool addSubject(const std::shared_ptr<Subject>& subject);
protected:
    ProfessorParticipant(int id, const std::unordered_map<int, std::shared_ptr<Subject>>& availableSubjects) : Participant(id), teachingSubjects(Prompt::forType<Subject>::getSelectablesFromInput("Select the subjects the professor teaches:", availableSubjects)) {};
    ProfessorParticipant(int id, std::string name, std::string cpf) : Participant(id, name, cpf) {};
private:
    int nextId() override;
    static int currentId;
    std::unordered_map<int, std::shared_ptr<Subject>> teachingSubjects;
};

#endif
