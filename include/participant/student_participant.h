#ifndef STUDENT_PARTICIPANT_H
#define STUDENT_PARTICIPANT_H

#include"participant.h"

class StudentParticipant : public Participant {
public:
    StudentParticipant(std::string name, std::string cpf) : Participant(nextId(), name, cpf) {};
    void printSelf() const override;
    int nextId() override;
private:
    static int currentId;
};

#endif
