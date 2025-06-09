#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include"named_entity.h"
#include"prompt.h"
#include"cpf.h"
#include<string>
#include<vector>

class Participant : public NamedEntity {
private:
    const CPF cpf;
public:
    static bool validateCPF(std::string cpf, bool verbose);
    void printSelf() const override;
protected:
    Participant(int id) : NamedEntity(id), cpf(Prompt::getTextFromInput("Enter the CPF:")) {};
    Participant(int id, std::string name, std::string cpfString) : NamedEntity(id, name), cpf(cpfString) {};
private:
    // std::string cpfFromInput(); // using prompt helper class now, it's cleaner
};
#endif
