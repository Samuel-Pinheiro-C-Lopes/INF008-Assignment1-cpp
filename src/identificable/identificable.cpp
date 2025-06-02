#include"identificable.h"

#include<iostream>

int Identificable::getId() const {
    return id;
}

void Identificable::printSelf() const {
    std::cout << "id: " << id << "." << std::endl;
}
