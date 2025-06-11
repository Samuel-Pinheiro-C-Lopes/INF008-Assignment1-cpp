#include"event_base.h"

#include"named_entity.h"
#include"date.h"

#include<iostream>

void EventBase::printSelf() const {
    std::cout << "Event name: ";
    NamedEntity::printSelf();
    std::cout << std::endl;
    std::cout << "Vacancies: " << vacancies << "." << std::endl;
    std::cout << "Date: " << this->date.getValue() << "." << std::endl;
}

const Date& EventBase::getDate() const {
    return this->date;
}

bool EventBase::isValid() const {
    return this->date.getValue().size() > 0 && NamedEntity::isValid();
}

Json EventBase::serializeSelf() const {
    Json json = NamedEntity::serializeSelf();
    json["date"] = this->date.getValue();
    return json;
}
