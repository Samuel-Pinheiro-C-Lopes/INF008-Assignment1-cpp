#ifndef ENTITY_H
#define ENTITY_H

#include<string>

class Entity {
private:
    const int id;
    const std::string name;
protected:
    Entity(int id, std::string name) : id(id), name(name) {};
    ~Entity() {};
    /* Id sequence for concrete
     * implementations */
    virtual int nextId() = 0;
public:
    /* A getter for the id can be handy
     * once we use STL containers and
     * need to find unique elements
     * or assign a unique key */
    int getId() const;
    /* All entities shall implement
     * an own way of printing itself -
     * although I think most
     * will use ascendant classes
     * implementations of this */
    virtual void printSelf() const;
};

#endif
