#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include"entity.h"

#include<set>

class University : public Entity {
public:
    University(std::string name) : Entity(nextId(), name) {};
    void printSelf() const override;
private:
    int nextId() override { return 0; }
};

#endif
