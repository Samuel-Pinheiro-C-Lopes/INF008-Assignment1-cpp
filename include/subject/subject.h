#ifndef SUBJECT_H
#define SUBJECT_H

#include"named_entity.h"
#include"prompt.h"

#include"alias.h"

#include<unordered_map>
#include<memory>

using namespace alias;

class Subject : public NamedEntity {
public:
    Subject() : NamedEntity(nextId()) {}

    Subject(
        String name
    ) : NamedEntity(nextId(), name) {};

    void printSelf() const override;
protected:
    int nextId() override;
    static int currentId;
};

#endif
