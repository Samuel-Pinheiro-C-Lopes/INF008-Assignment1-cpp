#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include"entity.h"
#include<string>
#include<vector>

class Participant : public Entity {
private:
    const std::string cpf;
public:
    static bool validateCPF(std::string cpf, bool verbose);
    void printSelf() const override;
protected:
    Participant(int id, std::string name, std::string cpf);
private:
    /* constexpr says it's evaluated at compiler time, meaning computation
     * can be handled by it - it's a good idiomatic practice, as it seems */
    static constexpr int VERIFIER_START = 9;
    static constexpr int VERIFIER_MULTIPLIER = 2;
    static char calculateVerifierDigit(std::vector<char>::iterator rbegin, std::vector<char>::iterator rend);
};
#endif
