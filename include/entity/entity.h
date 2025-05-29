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
    virtual int nextId() = 0;
public:
    int getId() const;
    std::string getName() const;
    virtual void printSelf() const;
};

#endif
