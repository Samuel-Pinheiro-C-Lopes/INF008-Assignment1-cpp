#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include"named_entity.h"

#include"prompt.h"
#include"cpf.h"

#include"alias.h"

#include<string>
#include<vector>

using namespace alias;

class Participant : public NamedEntity {
private:
    const CPF cpf;
public:
    static bool validateCPF(String cpf, bool verbose);
    void printSelf() const override;
    bool isValid() const override;
    Json serializeSelf() const override;
protected:
    Participant(int id) : NamedEntity(id), cpf(Prompt::getTextFromInput("Enter the CPF:")) {};
    Participant(int id, String name, String cpfString) : NamedEntity(id, name), cpf(cpfString) {};
private:
    // String cpfFromInput(); // using prompt helper class now, it's cleaner
};
#endif
