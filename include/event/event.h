#ifndef EVENT_H
#define EVENT_H

#include"event_base.h"
#include"participant.h"
#include"registration.h"
#include"registration_base.h"
#include"date.h"

#include<memory>
#include<unordered_map>
#include<chrono>
#include<type_traits>

/* abstract event class */
template<typename AttendeeType>
class Event : public EventBase {
    /* Asserts that the AttendeeType must be or inherit from Participant class.
     * It's the way I thought of to specify strict types of participants whitout needing to check
     * for instance in runtime, since I think this may be a bad practice (if I am not mistaken,
     * it hurts the Liskov Substitution Principle) */
    static_assert(std::is_base_of<Participant, AttendeeType>::value, "<AttendeeType> of Event must be derived from Participant class");
private:
    /* stores some derivation of Registration of some specific Participant type */
    std::unordered_map<int, std::shared_ptr<Registration<AttendeeType>>> attendeesRegistrations;

    /* Stores some derivation of participants in a unordered manner.
     * The keys are the ids, and the Values are the participants with corresponding id. */
    // std::unordered_map<int, std::shared_ptr<AttendeeType>> participants;
public:
    /* Each type of event will perform different ways of registration that
     * have behave in commom with a base one implemented in event.cpp */
    // virtual bool registerParticipant(const std::shared_ptr<AttendeeType>& participant);
    /* Overrides the print to show date and participants. */

    /* adds a registration */
    virtual bool addAttendeeRegistration(const std::shared_ptr<Registration<AttendeeType>>& attendeeRegistration);
    std::vector<int> getAttendesKeys() const;
    void printSelf() const override;
protected:
    Event(const int id, const std::string& name, const int vacancies, const std::string& date) : EventBase(id, name, vacancies, date) {};
    Event(const int id) : EventBase(id) {};


    template<typename RegistrationsType>
    std::vector<int> getParticipantsKeysFrom(const std::vector<std::shared_ptr<RegistrationsType>> source) const {
        static_assert(std::is_base_of<RegistrationBase, RegistrationsType>::value, "<RegistrationsType> of getParticipantsKeysFrom([...]) must be derived from RegistrationBase class");

        std::vector<int> participants;

        for (typename std::vector<std::shared_ptr<RegistrationsType>>::const_iterator itr = source.begin(); itr != source.end(); ++itr)
            participants.push_back(itr->getParticipantId());

        return participants;
    }

    template<typename RegistrationsType>
    std::vector<int> getParticipantsKeysFrom(const std::unordered_map<int, std::shared_ptr<RegistrationsType>> source) const {
        static_assert(std::is_base_of<RegistrationBase, RegistrationsType>::value, "<RegistrationsType> of getParticipantsKeysFrom([...]) must be derived from RegistrationBase class");

        std::vector<int> participants;

        for (typename std::unordered_map<int, std::shared_ptr<RegistrationsType>>::const_iterator itr = source.begin(); itr != source.end(); ++itr)
            participants.push_back(itr->second->getParticipantId());

        return participants;
    }

    template<typename ToBeRegisteredType>
    bool addRegistrationTo(std::unordered_map<int, std::shared_ptr<ToBeRegisteredType>>& registrationsTarget, std::shared_ptr<ToBeRegisteredType> toBeRegistered) {
        static_assert(std::is_base_of<RegistrationBase, ToBeRegisteredType>::value, "<ToBeRegisteredType> of addRegistrationTo([...]) must be derived from RegistrationBase class");
        if (vacancies == 0) return false;
        bool wasRegistrationInserted = registrationsTarget.insert(std::make_pair(toBeRegistered->getId(), toBeRegistered)).second;
        if (wasRegistrationInserted) vacancies--;
        return wasRegistrationInserted;
    }

    /* function overload to std::vector<std::shared_ptr<ToBeRegisteredType>> approachs
     * instead of the usual std::unordered_map<std::shared_ptr<ToBeRegisteredType>> */
    template<typename ToBeRegisteredType>
    bool addRegistrationTo(std::vector<std::shared_ptr<ToBeRegisteredType>>& registrationsTarget, std::shared_ptr<ToBeRegisteredType> toBeRegistered) {
        static_assert(std::is_base_of<RegistrationBase, ToBeRegisteredType>::value, "<ToBeRegisteredType> of addRegistrationTo([...]) must be derived from RegistrationBase class");
        if (vacancies == 0) return false;
        registrationsTarget.push_back(toBeRegistered);
        vacancies--;
        return true;
    }


    /*
    bool addRegistrationTo(std::unordered_map<int, std::shared_ptr<Registration<ToBeRegisteredType>>> registrationsTarget, std::shared_ptr<Registration<ToBeRegisteredType>> toBeRegistered) {
        static_assert(std::is_base_of<Participant, ToBeRegisteredType>::value, "<ToBeRegisteredType> of Event must be derived from Participant class");
        if (vacancies == 0) return false;
        bool wasRegistrationInserted = registrationsTarget.insert(std::make_pair(toBeRegistered->getId(), toBeRegistered)).second;
        if (wasRegistrationInserted) vacancies--;
        return wasRegistrationInserted;
    };
    */
};

#endif
