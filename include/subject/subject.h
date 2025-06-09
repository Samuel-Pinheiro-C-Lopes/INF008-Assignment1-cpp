#ifndef SUBJECT_H
#define SUBJECT_H

#include"named_entity.h"
#include"prompt.h"

#include<unordered_map>
#include<memory>

class Subject : public NamedEntity {
public:
    /* base fill from input constructor */
    Subject() : NamedEntity(nextId()) {}
    Subject(std::string name) : NamedEntity(nextId(), name) {};
    void printSelf() const override;
protected:
    int nextId() override;
    static int currentId;
};

#endif
