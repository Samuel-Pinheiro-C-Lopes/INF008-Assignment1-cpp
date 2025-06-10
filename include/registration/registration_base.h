#ifndef REGISTRATION_BASE_H
#define REGISTRATION_BASE_H

#include"participant.h"
#include"entity.h"
#include"date.h"

#include<string>
#include<memory>

class RegistrationBase : public Entity {
public:
    void printSelf() const override;
    int getParticipantId() const;
protected:
    RegistrationBase(int id) : Entity(id), date(), participant() {};

    RegistrationBase(int id, const std::shared_ptr<Participant>& participant) : Entity(id), date(), participant(participant) {};

    RegistrationBase(int id, const std::string& date, const std::shared_ptr<Participant>& participant) : Entity(id), date(date), participant(participant) {};
private:
    Date date;
    std::shared_ptr<Participant> participant;
};

#endif
