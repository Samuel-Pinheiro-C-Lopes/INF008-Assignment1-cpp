#include"subject.h"

#include"named_entity.h"

#include<iostream>
#include<unordered_map>
#include<memory>
#include<limits>

/* Default id sequence */
int Subject::currentId = 1;
int Subject::nextId() {
    return Subject::currentId++;
}

void Subject::printSelf() const {
    std::cout << "Subject: ";
    NamedEntity::printSelf();
    std::cout << "." << std::endl;
}
