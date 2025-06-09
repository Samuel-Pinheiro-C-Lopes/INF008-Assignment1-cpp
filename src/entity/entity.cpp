#include"entity.h"

#include<iostream>

int Entity::getId() const {
    return id;
}

void Entity::printSelf() const {
    std::cout << "id: " << id << "." << std::endl;
}
