#ifndef SUBJECT_H
#define SUBJECT_H

#include"entity.h"

class Subject : public Entity {
public:
    Subject(std::string name) : Entity(nextId(), name) {};
protected:
    int nextId() override;
    static int currentId;
};

#endif
