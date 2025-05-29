#ifndef EVENT_H
#define EVENT_H

#include"entity.h"
#include"participant.h"
#include<unordered_map>
#include<chrono>
#include<memory>

class Event : public Entity {
private:
    int vacancies;
    std::string date;
    std::unordered_map<int, std::shared_ptr<Participant>> participants;
public:
    virtual bool registerParticipant(std::shared_ptr<Participant> participant);
    void printSelf() const override;
protected:
    Event(int id, std::string name, int vacancies, std::string date) : Entity(id, name), vacancies(vacancies), date(date) {};
};

#endif
