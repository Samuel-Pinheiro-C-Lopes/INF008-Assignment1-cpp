#ifndef NAMED_ENTITY_H
#define NAMED_ENTITY_H

#include"entity.h"
#include"prompt.h"

#include<string>

class NamedEntity : public Entity {
private:
    const std::string name;
    // std::string nameFromInput(); // using prompt now... it's cleaner
protected:
    NamedEntity(int id) : Entity(id), name(Prompt::getTextFromInput("Enter the name field:")) {};
    NamedEntity(int id, std::string name) : Entity(id), name(name) {};
    ~NamedEntity() {};
public:
    /* Implements the print self for name */
    void printSelf() const override;
};

#endif
