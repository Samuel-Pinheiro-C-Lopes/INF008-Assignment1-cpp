#ifndef CPF_H
#define CPF_H

#include<string>
#include<vector>

class CPF {
public:
    static bool validateCPF(const std::string& cpf, const bool verbose);
    const std::string& getValue() const;
    CPF(const std::string& cpfString) : value(CPF::validateCPF(cpfString, VERBOSE) ? cpfString : "") {};
private:
    static constexpr bool VERBOSE = true;
    const std::string value;
    /* constexpr says it's evaluated at compiler time, meaning computation
     * can be handled by it - it's a good idiomatic practice, as it seems */
    static constexpr int VERIFIER_START = 9;
    static constexpr int VERIFIER_MULTIPLIER = 2;
    // static char calculateVerifierDigit(std::vector<char>::iterator rbegin, std::vector<char>::iterator rend);
    static char calculateVerifierDigit(const std::vector<char>& digits, int length);
};

#endif
