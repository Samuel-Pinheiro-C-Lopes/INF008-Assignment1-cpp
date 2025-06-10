#ifndef IN_PERSON_EVENT_REGISTRATION_H
#define IN_PERSON_EVENT_REGISTRATION_H

#include"registration.h"
#include"participant.h"
#include"prompt.h"

#include<string>
#include<unordered_map>
#include<memory>

template<typename ParticipantType>
class InPersonEventRegistration : public Registration<ParticipantType> {
public:
    void printSelf() const override;

    /* input based when there is no available participants */
    InPersonEventRegistration() : Registration<ParticipantType>(nextId()), accessibility(Prompt::getFlagFromInput("Do you have any kind of disability? Enter if you need accessibility support:")) {};

    InPersonEventRegistration(const std::unordered_map<int, std::shared_ptr<ParticipantType>>& availableParticipants) : Registration<ParticipantType>(nextId(), availableParticipants), accessibility(Prompt::getFlagFromInput("Do you have any kind of disability? Enter if you need accessibility support:")) {};

    InPersonEventRegistration(const std::string& date, const std::shared_ptr<ParticipantType>& participant, bool accessibility) : Registration<ParticipantType>(nextId(), date, participant), accessibility(accessibility) {};
private:
    bool accessibility;
    int nextId() override;
    static int currentId;
};

#endif
