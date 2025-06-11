#ifndef WORKSHOP_EVENT_H
#define WORKSHOP_EVENT_H

#include"subject.h"
#include"event.h"
#include"prompt.h"
#include"student_participant.h"
#include"external_participant.h"
#include"professor_participant.h"

#include"alias.h"

#include<memory>
#include<string>
#include<unordered_map>
#include<vector>

using namespace alias;

class WorkshopEvent : public Event<StudentParticipant> {
public:
    WorkshopEvent(
        const String& name,
        const int vacancies,
        const String& date,
        const Map<int, Ptr<ProfessorParticipant>>& professors,
        const Ptr<Subject>& subject
    ) : Event(nextId(), name, vacancies, date), professors(professors), subject(subject) {};

    WorkshopEvent(
        const Map<int, Ptr<Subject>>& availableSubjects,
        const Map<int, Ptr<ProfessorParticipant>>& availableProfessors
    ) : Event(nextId()),
        subject(Prompt::forType<Subject>::getSelectableFromInput("Select the subject for the workshop:", availableSubjects)),
        professors(Prompt::forType<ProfessorParticipant>::getSelectablesFromInput("Select the professors for the workshop:", availableProfessors)) {};

    bool addGuestRegistration(const Ptr<Registration<ExternalParticipant>>& guestRegistration);
    Vector<int> getGuestsKeys() const;
    void printSelf() const override;
    Json serializeSelf() const override;
private:
    static int currentId;
    int nextId() override;
    Ptr<Subject> subject;
    Map<int, Ptr<ProfessorParticipant>> professors;
    Map<int, Ptr<Registration<ExternalParticipant>>> guestsRegistrations;
};

#endif
