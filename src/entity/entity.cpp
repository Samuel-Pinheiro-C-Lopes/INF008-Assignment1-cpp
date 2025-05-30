#include"entity.h"
#include<string>
#include<iostream>

int Entity::getId() const {
    return id;
}

/* Default behavior, just print
 * the name */
void Entity::printSelf() const {
    std::cout << "Name: " << name << "." << std::endl;
}
