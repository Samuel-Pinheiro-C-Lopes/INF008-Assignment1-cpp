#ifndef PROFESSOR_PARTICIPANT_H
#define PROFESSOR_PARTICIPANT_H

#include"participant.h"
#include"subject.h"

#include<unordered_map>

class ProfessorParticipant : public Participant {
public:
    void printSelf() const override;
    bool teaches(Subject* subject) const;
    bool addSubject(Subject* subject);
protected:
    ProfessorParticipant(int id, std::string name, std::string cpf) : Participant(id, name, cpf) {};
private:
    std::unordered_map<int, Subject*> subjects;
    int nextId() override;
    static int currentId;
};

#endif
