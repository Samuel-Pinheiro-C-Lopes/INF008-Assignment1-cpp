#include"participant.h"
#include"entity.h"

#include<iostream>

void Participant::printSelf() const {
    Entity::printSelf();
    std::cout << "CPF: " << cpf << "." << std::endl;
}
