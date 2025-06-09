#include"subject.h"

#include"named_entity.h"

#include<iostream>
#include<unordered_map>
#include<memory>
#include<limits>

/* Default id sequence */
int Subject::currentId = 0;
int Subject::nextId() {
    std::cout << Subject::currentId << std::endl;
    return Subject::currentId++;
}

void Subject::printSelf() const {
    std::cout << "Subject: ";
    NamedEntity::printSelf();
    std::cout << "." << std::endl;
}
