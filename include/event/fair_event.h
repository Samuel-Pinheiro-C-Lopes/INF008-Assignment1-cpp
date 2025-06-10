#ifndef FAIR_EVENT_H
#define FAIR_EVENT_H

#include"event.h"
#include"external_participant.h"
#include"subject.h"
#include"student_participant.h"
#include"prompt.h"
#include"registration.h"

#include<unordered_map>
#include<memory>
#include<vector>

/* This event could have many Presenters and guests */
class FairEvent : public Event<ExternalParticipant> {
public:
    FairEvent(const std::string& name, const int vacancies, const std::string& date) : Event(nextId(), name, vacancies, date) {};

    FairEvent() : Event(nextId()) {};
    void printSelf() const override;
    bool addPresenterRegistration(const std::shared_ptr<Registration<StudentParticipant>>& presenterRegistration);
    std::vector<int> getPresentersKeys() const;
private:
    std::unordered_map<int, std::shared_ptr<Registration<StudentParticipant>>> presentersRegistrations;
    std::unordered_map<int, std::shared_ptr<Subject>> subjects;
    static int currentId;
    int nextId() override;
};

#endif
