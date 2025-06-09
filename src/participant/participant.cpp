#include"participant.h"
#include"named_entity.h"

#include<iostream>
#include<string>
#include<vector>

/*
Participant::Participant(int id, std::string name, std::string cpf) : NamedEntity(id, name), cpf(!Participant::validateCPF(cpf, true) ? cpf : "") {
    if (this->cpf.empty())
        std::cout << "CPF: " << cpf << " is not valid." << std::endl;
}
*/

void Participant::printSelf() const {
    NamedEntity::printSelf();
    std::cout << std::endl;
    std::cout << "CPF: " << cpf.getValue() << "." << std::endl;
}

/*
std::string Participant::cpfFromInput() {
    std::string cpf;
    std::cin >> cpf;
    if (Participant::validateCPF(cpf, true))
        return cpf;
    std::cout << "CPF: " << cpf << " is not valid." << std::endl;
    return "";
}
*/
