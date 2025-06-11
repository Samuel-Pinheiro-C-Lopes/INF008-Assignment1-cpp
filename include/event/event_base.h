#ifndef EVENT_BASE_H
#define EVENT_BASE_H

#include"date.h"
#include"named_entity.h"
#include"alias.h"

#include<string>

using namespace alias;

class EventBase : public NamedEntity {
private:
    Date date;
protected:
    int vacancies;
public:
    EventBase(
        const int id,
        const String& name,
        const int vacancies,
        const String& date
    ) : NamedEntity(id, name), vacancies(vacancies), date(date) {};

    EventBase(const int id) : NamedEntity(id),
        vacancies(Prompt::getIntFromInput("Enter with the number of vacancies for the event:")),
        date(Prompt::getTextFromInput("Enter with the date for the event (format: [dd/MM/yyy] or [dd-MM-yyyy]): ")) {};

    void printSelf() const override;
    const Date& getDate() const;
    bool isValid() const override;
    Json serializeSelf() const override;
};

#endif
