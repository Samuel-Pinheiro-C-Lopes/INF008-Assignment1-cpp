#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include"entity.h"
#include<string>

class Participant : public Entity {
private:
    const std::string cpf;
public:
    void printSelf() const override;
protected:
    Participant(int id, std::string name, std::string cpf) : Entity(id, name) {};
};
#endif
