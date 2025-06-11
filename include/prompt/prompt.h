#ifndef PROMPT_H
#define PROMPT_H

#include"entity.h"

#include"alias.h"

#include<memory>
#include<type_traits>
#include<unordered_map>
#include<vector>

using namespace alias;

/* static class for prompt utilities
 * final prevents inheritance
 * constructors = delete tells compiler to not allow instances
 * destructor = delete tells compiler to not allow destruction
 * (both ensure no initialization) */
class Prompt final {
public:
    /* gets text input from user */
    static String getTextFromInput(const String& title);
    /* gets a boolean flag from user input */
    static bool getFlagFromInput(const String& title);
    /* gets a number from user input */
    static int getIntFromInput(const String& title);
    
    static void printFullSeparator();

    static void printPartialSeparator();

    static void printHugeSeparator();

    /* strings as options */
    static void printSelectablesAsOptions(const Map<int, String>& selectables);

    static bool handleLastCinInput(int& input);
    // evaluates cin input based on the last std::cin input and int range
    static bool handleLastCinInput(int& input, const int rangeStart, const int rangeEnd);

    static bool handleLastCinInput(int& input, const Map<int, String>& options);

    static int getOptionFromInput(const Map<int, String>& options);

    template<typename T>
    class forType final {
            static_assert(std::is_base_of<Entity, T>::value, "<T> from Prompt must derive from the Entity class.");
    public:
        /* returns a unordered map based on the input selection from the available sources */
        static Map<int, Ptr<T>> getSelectablesFromInput(const String& selectionTitle, const Map<int, Ptr<T>>& availableSelectables);

        /* returns a pointer based on the selection from an available source */
        static Ptr<T> getSelectableFromInput(const String& selectionTitle, const Map<int, Ptr<T>>& availableSelectables);

        static void printSelectablesAsOptions(const Map<int, Ptr<T>>& selectables);

        static void printSelectables(const Map<int, Ptr<T>>& selectables);

        static void printSelectables(const Vector<Ptr<T>>& selectables);

        static void printSelectables(const Vector<T>& selectables);

        static bool handleLastCinInput(int& input, const Map<int, Ptr<T>>& options);

        static bool handleLastCinInput(int& input, const Map<int, T>& options);

        static bool handleLastCinInput(int& input, const Map<int, Ptr<T>>& options, const Map<int, Ptr<T>>& alreadySelectedOptions);

        forType() = delete;
        ~forType() = delete;
    };

    /* compiler error if a initialization of this class is made */
    Prompt() = delete;
    ~Prompt() = delete;
};

#endif
