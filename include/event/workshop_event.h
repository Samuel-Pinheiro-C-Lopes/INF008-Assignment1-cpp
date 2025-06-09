#ifndef WORKSHOP_EVENT_H
#define WORKSHOP_EVENT_H

#include"subject.h"
#include"event.h"
#include"prompt.h"
#include"student_participant.h"
#include"external_participant.h"
#include"professor_participant.h"

#include<memory>
#include<string>
#include<unordered_map>

class WorkshopEvent : public Event<StudentParticipant> {
public:
    WorkshopEvent(const std::string& name, const int vacancies, const std::string& date, const std::unordered_map<int, std::shared_ptr<ProfessorParticipant>>& professors, const std::shared_ptr<Subject>& subject) : Event(nextId(), name, vacancies, date), professors(professors), subject(subject) {};

    WorkshopEvent(const std::unordered_map<int, std::shared_ptr<Subject>>& availableSubjects, const std::unordered_map<int, std::shared_ptr<ProfessorParticipant>>& availableProfessors) : Event(nextId()), subject(Prompt::forType<Subject>::getSelectableFromInput("Select the subject for the workshop:", availableSubjects)), professors(Prompt::forType<ProfessorParticipant>::getSelectablesFromInput("Select the professors for the workshop:", availableProfessors)) {};

    bool addGuestRegistration(const std::shared_ptr<Registration<ExternalParticipant>>& guestRegistration);
    void printSelf() const override;
private:
    static int currentId;
    int nextId() override;
    std::shared_ptr<Subject> subject;
    std::unordered_map<int, std::shared_ptr<ProfessorParticipant>> professors;
    std::unordered_map<int, std::shared_ptr<Registration<ExternalParticipant>>> guestsRegistrations;
};

#endif
