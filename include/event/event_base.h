#ifndef EVENT_BASE_H
#define EVENT_BASE_H

#include"date.h"
#include"named_entity.h"

#include<string>

class EventBase : public NamedEntity {
private:
    Date date;
protected:
    int vacancies;
public:
    EventBase(const int id, const std::string& name, const int vacancies, const std::string& date) : NamedEntity(id, name), vacancies(vacancies), date(date) {};
    EventBase(const int id) : NamedEntity(id), vacancies(Prompt::getIntFromInput("Enter with the number of vacancies for the event:")), date(Prompt::getTextFromInput("Enter with the date for the event (format: [dd/MM/yyy] or [dd-MM-yyyy]): ")) {};

    void printSelf() const override;
    const Date& getDate() const;
};

#endif
