#ifndef EXTERNAL_PARTICIPANT_H
#define EXTERNAL_PARTICIPANT_H

#include"participant.h"
#include"prompt.h"

#include"alias.h"

#include<string>

using namespace alias;

class ExternalParticipant : public Participant {
public:
    ExternalParticipant() : Participant(nextId()), originUniversity(Prompt::getTextFromInput("Enter with the university of origin of this external participant: ")) {};

    ExternalParticipant(
        String name,
        String cpf,
        String originUniversity) : Participant(nextId(), name, cpf), originUniversity(originUniversity) {};

    void printSelf() const override;
    Json serializeSelf() const override;
private:
    static int currentId;
    int nextId() override;
    String originUniversity;
};

#endif
