#ifndef EXTERNAL_PARTICIPANT_H
#define EXTERNAL_PARTICIPANT_H

#include"participant.h"

#include<string>

class ExternalParticipant : public Participant {
public:
    ExternalParticipant() : Participant(nextId()), originUniversity(originUniversityFromInput()) {};

    ExternalParticipant(std::string name, std::string cpf, std::string originUniversity) : Participant(nextId(), name, cpf), originUniversity(originUniversity) {};

    void printSelf() const override;
private:
    static int currentId;
    int nextId() override;
    std::string originUniversity;
    std::string originUniversityFromInput();
};

#endif
