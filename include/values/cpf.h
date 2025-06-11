#ifndef CPF_H
#define CPF_H

#include"alias.h"

#include<string>
#include<vector>

using namespace alias;

class CPF {
public:
    static bool validateCPF(
        const String& cpf,
        const bool verbose
    );

    const String& getValue() const;

    CPF(
        const String& cpfString
    ) : value(CPF::validateCPF(cpfString, VERBOSE) ? cpfString : "") {};

private:
    static constexpr bool VERBOSE = true;
    const String value;
    /* constexpr says it's evaluated at compiler time, meaning computation
     * can be handled by it - it's a good idiomatic practice, as it seems */
    static constexpr int VERIFIER_START = 9;
    static constexpr int VERIFIER_MULTIPLIER = 2;
    // static char calculateVerifierDigit(Vector<char>::iterator rbegin, Vector<char>::iterator rend);
    static char calculateVerifierDigit(
        const Vector<char>& digits,
        int length
    );
};

#endif
