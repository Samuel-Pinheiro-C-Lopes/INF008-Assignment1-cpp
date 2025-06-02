#ifndef ONLINE_EVENT_REGISTRATION_H
#define ONLINE_EVENT_REGISTRATION_H

#include"registration.h"
#include"participant.h"
#include"prompt.h"

#include<memory>
#include<unordered_map>
#include<string>

/* registration in the online demeanor requires an e-mail for contact */
template<typename ParticipantType>
class OnlineEventRegistration : public Registration<ParticipantType> {
public:
    void printSelf() const override;
    /* input based constructor */
    OnlineEventRegistration(const std::unordered_map<int, std::shared_ptr<ParticipantType>>& availableParticipants) : Registration<ParticipantType>(nextId(), availableParticipants), contactEmail(Prompt::getTextFromInput("Enter with a e-mail for contact:")) {};

    /* default constructor */
    OnlineEventRegistration(const std::string& date, const std::shared_ptr<ParticipantType>& participant, const std::string& contactEmail) :  Registration<ParticipantType>(nextId(), date, participant), contactEmail(contactEmail) {};

private:
    std::string contactEmail;
    int nextId() override;
    static int currentId;
};

#endif
