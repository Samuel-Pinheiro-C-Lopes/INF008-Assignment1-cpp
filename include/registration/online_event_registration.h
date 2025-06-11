#ifndef ONLINE_EVENT_REGISTRATION_H
#define ONLINE_EVENT_REGISTRATION_H

#include"registration.h"
#include"participant.h"
#include"prompt.h"

#include"alias.h"

#include<memory>
#include<unordered_map>
#include<string>

using namespace alias;

/* registration in the online demeanor requires an e-mail for contact */
template<typename T>
class OnlineEventRegistration : public Registration<T> {
public:
    void printSelf() const override;
    /* input based when there is no available participants */
    OnlineEventRegistration() : Registration<T>(nextId()),
    contactEmail(Prompt::getTextFromInput("Enter with a e-mail for contact:")) {};

    /* input based constructor based on available participants */
    OnlineEventRegistration(
        const Map<int, Ptr<T>>& availableParticipants
    ) : Registration<T>(nextId(), availableParticipants), contactEmail(Prompt::getTextFromInput("Enter with a e-mail for contact:")) {};

    /* default constructor */
    OnlineEventRegistration(
        const String& date,
        const Ptr<T>& participant,
        const String& contactEmail
    ) :  Registration<T>(nextId(), date, participant), contactEmail(contactEmail) {};

private:
    String contactEmail;
    int nextId() override;
    static int currentId;
};

#endif
