#include"named_entity.h"

#include<iostream>

/* Default behavior, just print
 * the name. Print the id isn't normally what
 * we want. */
void NamedEntity::printSelf() const {
    std::cout << name;
}

bool NamedEntity::isValid() const {
    return this->name.size() > 0;
}


Json NamedEntity::serializeSelf() const {
    Json json = Entity::serializeSelf();
    json["name"] = this->name;
    return json;
}
