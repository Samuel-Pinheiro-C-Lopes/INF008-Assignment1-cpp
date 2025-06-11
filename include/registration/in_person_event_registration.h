#ifndef IN_PERSON_EVENT_REGISTRATION_H
#define IN_PERSON_EVENT_REGISTRATION_H

#include"registration.h"
#include"participant.h"
#include"prompt.h"

#include"alias.h"

#include<string>
#include<unordered_map>
#include<memory>

using namespace alias;

template<typename T>
class InPersonEventRegistration : public Registration<T> {
public:
    void printSelf() const override;

    /* input based when there is no available participants */
    InPersonEventRegistration() : Registration<T>(nextId()), accessibility(Prompt::getFlagFromInput("Do you have any kind of disability? Enter if you need accessibility support:")) {};

    InPersonEventRegistration(
        const Map<int, Ptr<T>>& availableParticipants
    ) : Registration<T>(nextId(), availableParticipants), accessibility(Prompt::getFlagFromInput("Do you have any kind of disability? Enter if you need accessibility support:")) {};

    InPersonEventRegistration(
        const String& date,
        const Ptr<T>& participant,
        bool accessibility
    ) : Registration<T>(nextId(), date, participant), accessibility(accessibility) {};

private:
    bool accessibility;
    int nextId() override;
    static int currentId;
};

#endif
