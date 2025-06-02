#ifndef FAIR_EVENT_H
#define FAIR_EVENT_H

#include"event.h"
#include"participant.h"
#include"subject.h"
#include"prompt.h"
#include"registration"

#include<unordered_map>
#include<memory>

/* This event could have many Presenters and guests */
class FairEvent : public Event<Participant> {
public:
    FairEvent(std::string name, int vacancies, std::string date) : Event(nextId(), name, vacancies, date);
    void printSelf() const override;
private:
    std::unordered_map<int, std::shared_ptr<Registration<Participant>>> presenters;
    std::unordered_map<int, std::shared_ptr<Subject>> subjects;
    static int currentId;
    int nextId() override;
};

#endif
