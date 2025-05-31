#ifndef PROFESSOR_PARTICIPANT_H
#define PROFESSOR_PARTICIPANT_H

#include"participant.h"

class ProfessorParticipant : public Participant {
public:
    void printSelf() const override;
protected:
    ProfessorParticipant(int id, std::string name, std::string cpf) : Participant(id, name, cpf) {};
};

#endif
