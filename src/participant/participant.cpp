#include"participant.h"

#include<iostream>

void Participant::printSelf() const {
    NamedEntity::printSelf();
    std::cout << std::endl;
    std::cout << "CPF: " << cpf.getValue() << "." << std::endl;
}

bool Participant::isValid() const {
    return this->cpf.getValue().size() > 0 && NamedEntity::isValid();
}


Json Participant::serializeSelf() const {
    Json json = NamedEntity::serializeSelf();
    json["cpf"] = this->cpf.getValue();
    return json;
}
