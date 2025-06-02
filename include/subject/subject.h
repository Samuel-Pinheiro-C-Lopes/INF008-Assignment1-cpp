#ifndef SUBJECT_H
#define SUBJECT_H

#include"entity.h"
#include"prompt.h"

#include<unordered_map>
#include<memory>

class Subject : public Entity {
public:
    /* base fill from input constructor */
    Subject() : Entity(nextId()) {}
    Subject(std::string name) : Entity(nextId(), name) {};
protected:
    int nextId() override;
    static int currentId;
};

#endif
