#ifndef EVENT_H
#define EVENT_H

#include"entity.h"
#include"participant.h"
#include<unordered_map>
#include<chrono>
#include<type_traits>

/* abstract event class */
template<typename ParticipantType>
class Event : public Entity {
    /* Asserts that the ParticipantType must
     * be or inherit from Participant class.
     * It's the way I thought of to specify
     * strict types of participants
     * whitout needing to
     * check for instance in runtime, since
     * I think this may be a bad practice
     * (if I am not mistaken, it hurts the
     * Liskov Substitution Principle )*/
    static_assert(std::is_base_of<Participant, ParticipantType>::value, "<ParticipantType> of Event <ParticipantType> must be derived from Participant class");
private:
    int vacancies;
    std::string date;
    /* Stores some derivation of participants
     * in a unordered manner. It's more
     * performatic than the ordered version
     * and ordering isn't quite needed.
     * The keys are the ids, and the
     * Values the participants with
     * the id. */
    std::unordered_map<int, ParticipantType*> participants;
public:
    /* Each type of event will perform
     * different ways of registration that
     * have behave in commom with a base one
     * implemented in event.cpp */
    virtual bool registerParticipant(ParticipantType* participant);
    /* Overrides the print to show date
     * and participants. */
    void printSelf() const override;
protected:
    Event(int id, std::string name, int vacancies, std::string date) : Entity(id, name), vacancies(vacancies), date(date) {};
};

#endif
