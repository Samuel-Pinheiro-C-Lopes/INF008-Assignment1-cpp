#include"participant.h"
#include"entity.h"

#include<iostream>
#include<string>
#include<vector>

Participant::Participant(int id, std::string name, std::string cpf) : Entity(id, name), cpf(!Participant::validateCPF(cpf, true) ? cpf : "") {
    if (this->cpf.empty())
        std::cout << "CPF: " << cpf << " is not valid." << std::endl;
}

void Participant::printSelf() const {
    Entity::printSelf();
    std::cout << "CPF: " << cpf << "." << std::endl;
}

std::string Participant::cpfFromInput() {
    std::string cpf;
    std::cin >> cpf;
    if (Participant::validateCPF(cpf, true))
        return cpf;
    std::cout << "CPF: " << cpf << " is not valid." << std::endl;
    return "";
}

/* constexpr says it's evaluated at compiler time, meaning computation
 * can be handled by it - it's a good idiomatic practice, as it seems */
// constexpr int Participant::VERIFIER_START = 9;
// constexpr int Participant::VERIFIER_MULTIPLIER = 2;

/* Validates the CPF by lenght, occurrence of not numeric chars, distinct chars,
 * and verifier digits, also printing the error when 'verbose' is true */
bool Participant::validateCPF(std::string cpf, bool verbose) {
    std::vector<char> cpfDigits;
    bool noDistinct = true;

    for (std::string::iterator i = cpf.begin(); i != cpf.end(); i++) {
        /* Verify if current is a point or dash and, if that's the case, continues
         * without worries unless there are more than one consecutively */
        if ((*i) == '.' || (*i) == '-') {
            if (std::next(i) == cpf.end() || *std::next(i) == '.' || *std::next(i) == '-') {
                if (verbose)
                    std::cout << "Occurrence of sequential '.' or/and '-' in the CPF: " << cpf << "." << std::endl;
                return false;
            }
            continue;
        }
        /* Verifies if it's a number, since it's not a '-' or '.', and, if
         * that's the case, append to the copy */
        if ((*i) < '0' || (*i) > '9') {
            if (verbose)
                std::cout << "Occurrence of non dash, point or number in the CPF: " << cpf << "." << std::endl;
            return false;
        }
        /* Also verifies if there is a occurrence of a noDistinct digit */
        if (!cpfDigits.empty() && cpfDigits.back() != (*i))
            noDistinct = false;
        cpfDigits.push_back((*i));
    }

    /* default size for a cpf */
    if (cpfDigits.size() != 11)
        return false;

    /* if they are all the same, it's invalid as well */
    if (noDistinct)
        return false;

    /* Finding the verifier digits acconding to the first cpf digits */
    char firstVerifierDigit = calculateVerifierDigit(cpfDigits.begin() + VERIFIER_START, cpfDigits.begin());
    char secondVerifierDigit = calculateVerifierDigit(cpfDigits.begin() + VERIFIER_START + 1, cpfDigits.begin());

    /* check for equality */
    if (cpfDigits[VERIFIER_START] != firstVerifierDigit || cpfDigits[VERIFIER_START + 1] != secondVerifierDigit) {
        if (verbose)
            std::cout << "Occurrence of not valid verifier digit in CPF: " << cpf << "." << std::endl;
        return false;
    }

    return true;
}

char Participant::calculateVerifierDigit(std::vector<char>::iterator rbegin, std::vector<char>::iterator rend) {
    int sum = 0;
    int remainder;
    int currentMultiplier = VERIFIER_MULTIPLIER;
    /* default error value */
    if (rbegin <= rend)
        return -1;
    for (; rbegin != rend; currentMultiplier++, rbegin--)
        sum += (*rbegin) * currentMultiplier;
    remainder = sum%11;
    if (remainder < 2)
        return 0;
    return 11 - remainder;
}
