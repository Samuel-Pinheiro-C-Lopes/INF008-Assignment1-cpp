#include"entity.h"
#include<string>
#include<iostream>

int Entity::getId() const {
    return id;
}

std::string Entity::getName() const {
    return name;
}

void Entity::printSelf() const {
    std::cout << "Name: " << name << "." << std::endl;
}
