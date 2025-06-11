#ifndef EVENT_H
#define EVENT_H

#include"event_base.h"
#include"participant.h"
#include"registration.h"
#include"registration_base.h"
#include"date.h"
#include"alias.h"

#include<memory>
#include<unordered_map>
#include<chrono>
#include<type_traits>
#include<vector>

using namespace alias;

/* abstract event class */
template<typename T>
class Event : public EventBase {
    /* Asserts that the T must be or inherit from Participant class.
     * It's the way I thought of to specify strict types of participants whitout needing to check for instance in runtime, since I think this may be a bad practice (if I am not mistaken, it hurts the Liskov Substitution Principle) */
    static_assert(std::is_base_of<Participant, T>::value, "<T> of Event must be derived from Participant class");
private:
    Map<int, Ptr<Registration<T>>> attendeesRegistrations;
public:
    /* adds a registration */
    virtual bool addAttendeeRegistration(const Ptr<Registration<T>>& attendeeRegistration);

    std::vector<int> getAttendesKeys() const;

    void printSelf() const override;
    Json serializeSelf() const override;
protected:
    Event(
        const int id,
        const String& name,
        const int vacancies,
        const String& date) : EventBase(id, name, vacancies, date) {};

    Event(const int id) : EventBase(id) {};

    template<typename G>
    std::vector<int> getParticipantsKeysFrom(
        const Vector<Ptr<G>>& source
    ) const {
        static_assert(std::is_base_of<RegistrationBase, G>::value, "<G> of getParticipantsKeysFrom([...]) must be derived from RegistrationBase class");

        Vector<int> participants;

        for (typename Vector<Ptr<G>>::const_iterator itr = source.begin(); itr != source.end(); ++itr)
            participants.push_back(itr->getParticipantId());

        return participants;
    }

    template<typename G>
    Vector<int> getParticipantsKeysFrom(
        const Map<int, Ptr<G>>& source
    ) const {
        static_assert(std::is_base_of<RegistrationBase, G>::value, "<G> of getParticipantsKeysFrom([...]) must be derived from RegistrationBase class");

        Vector<int> participants;

        for (typename Map<int, Ptr<G>>::const_iterator itr = source.begin(); itr != source.end(); ++itr)
            participants.push_back(itr->second->getParticipantId());

        return participants;
    }

    template<typename G>
    bool addRegistrationTo(
        Map<int, Ptr<G>>& registrationsTarget,
        Ptr<G> toBeRegistered
    ) {
        static_assert(std::is_base_of<RegistrationBase, G>::value, "<G> of addRegistrationTo([...]) must be derived from RegistrationBase class");

        if (vacancies == 0) return false;

        bool wasRegistrationInserted = registrationsTarget.insert(std::make_pair(toBeRegistered->getId(), toBeRegistered)).second;

        if (wasRegistrationInserted) vacancies--;
        return wasRegistrationInserted;
    }

    /* function overload to std::vector<std::shared_ptr<G>> approachs
     * instead of the usual std::unordered_map<std::shared_ptr<G>> */
    template<typename G>
    bool addRegistrationTo(
        Vector<Ptr<G>>& registrationsTarget,
        Ptr<G> toBeRegistered
    ) {
        static_assert(std::is_base_of<RegistrationBase, G>::value, "<G> of addRegistrationTo([...]) must be derived from RegistrationBase class");

        if (vacancies == 0) return false;

        registrationsTarget.push_back(toBeRegistered);
        vacancies--;

        return true;
    }
};

#endif
