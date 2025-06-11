#ifndef FAIR_EVENT_H
#define FAIR_EVENT_H

#include"event.h"
#include"external_participant.h"
#include"subject.h"
#include"student_participant.h"
#include"prompt.h"
#include"registration.h"

#include"alias.h"

#include<unordered_map>
#include<memory>
#include<vector>

using namespace alias;

/* This event could have many Presenters and guests */
class FairEvent : public Event<ExternalParticipant> {
public:
    FairEvent(
        const String& name,
        const int vacancies,
        const String& date) : Event(nextId(), name, vacancies, date) {};

    FairEvent() : Event(nextId()) {};

    void printSelf() const override;
    bool addPresenterRegistration(const Ptr<Registration<StudentParticipant>>& presenterRegistration);
    Vector<int> getPresentersKeys() const;
    Json serializeSelf() const override;
private:
    Map<int, Ptr<Registration<StudentParticipant>>> presentersRegistrations;
    Map<int, Ptr<Subject>> subjects;
    static int currentId;
    int nextId() override;
};

#endif
