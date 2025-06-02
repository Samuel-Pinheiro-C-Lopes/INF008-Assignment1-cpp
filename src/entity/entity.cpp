#include"entity.h"
#include<string>
#include<iostream>
/*
int Entity::getId() const {
    return id;
}
*/

/* Default behavior, just print
 * the name. Print the id isn't normally what
 * we want. */
void Entity::printSelf() const {
    std::cout << "Name: " << name << "." << std::endl;
}

std::string Entity::nameFromInput() {
    std::string name;
    std::cout << "Enter the name field: ";
    std::cin >> name;
    return name;
}
