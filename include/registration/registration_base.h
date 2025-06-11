#ifndef REGISTRATION_BASE_H
#define REGISTRATION_BASE_H

#include"participant.h"
#include"entity.h"
#include"date.h"

#include"alias.h"

#include<string>
#include<memory>

using namespace alias;

class RegistrationBase : public Entity {
public:
    void printSelf() const override;
    int getParticipantId() const;
protected:
    RegistrationBase(int id) : Entity(id), date(), participant() {};

    RegistrationBase(int id, const Ptr<Participant>& participant) : Entity(id), date(), participant(participant) {};

    RegistrationBase(int id, const String& date, const Ptr<Participant>& participant) : Entity(id), date(date), participant(participant) {};
private:
    Date date;
    Ptr<Participant> participant;
};

#endif
