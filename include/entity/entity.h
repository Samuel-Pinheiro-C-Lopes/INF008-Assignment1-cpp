#ifndef ENTITY_H
#define ENTITY_H

#include"identificable.h"

#include<string>

class Entity : public Identificable {
private:
    const std::string name;
    std::string nameFromInput();
protected:
    Entity(int id) : Identificable(id), name(nameFromInput()) {};
    Entity(int id, std::string name) : Identificable(id), name(name) {};
    ~Entity() {};
public:
    /* Implements the print self for name */
    void printSelf() const override;
};

#endif
