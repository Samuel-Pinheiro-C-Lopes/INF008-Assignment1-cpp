#ifndef EVENT_H
#define EVENT_H

#include"entity.h"
#include"participant.h"
#include"registration.h"

#include<memory>
#include<unordered_map>
#include<chrono>
#include<type_traits>

/* abstract event class */
template<typename ParticipantType>
class Event : public Entity {
    /* Asserts that the ParticipantType must be or inherit from Participant class.
     * It's the way I thought of to specify strict types of participants
     * whitout needing to check for instance in runtime, since
     * I think this may be a bad practice (if I am not mistaken,
     * it hurts the Liskov Substitution Principle) */
    static_assert(std::is_base_of<Participant, ParticipantType>::value, "<ParticipantType> of Event must be derived from Participant class");
private:
    int vacancies;
    std::string date;

    /* stores some derivation of Registration of some specific Participant type */
    std::unordered_map<int, std::shared_ptr<Registration<ParticipantType>>> registrations;

    /* Stores some derivation of participants in a unordered manner.
     * The keys are the ids, and the Values are the participants with corresponding id. */
    // std::unordered_map<int, std::shared_ptr<ParticipantType>> participants;
public:
    /* Each type of event will perform different ways of registration that
     * have behave in commom with a base one implemented in event.cpp */
    // virtual bool registerParticipant(const std::shared_ptr<ParticipantType>& participant);
    /* Overrides the print to show date and participants. */

    /* adds a registration */
    virtual bool addRegistration(const std::shared_ptr<Registration<ParticipantType>>& registration);
    void printSelf() const override;
protected:
    Event(int id, std::string name, int vacancies, std::string date) : Entity(id, name), vacancies(vacancies), date(date) {};
};

#endif
