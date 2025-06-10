#ifndef PROMPT_H
#define PROMPT_H

#include"entity.h"

#include<memory>
#include<type_traits>
#include<unordered_map>
#include<vector>

/* static class for prompt utilities
 * final prevents inheritance
 * constructors = delete tells compiler to not allow instances
 * destructor = delete tells compiler to not allow destruction
 * (both ensure no initialization) */
class Prompt final {
public:
    /* gets text input from user */
    static std::string getTextFromInput(const std::string& title);
    /* gets a boolean flag from user input */
    static bool getFlagFromInput(const std::string& title);
    /* gets a number from user input */
    static int getIntFromInput(const std::string& title);
    
    static void printFullSeparator();

    static void printPartialSeparator();

    static void printHugeSeparator();

    static int getOptionFromInput(const std::unordered_map<int, std::string>& options);

    template<typename SelectableType>
    class forType final {
            static_assert(std::is_base_of<Entity, SelectableType>::value, "<SelectableType> from Prompt must derive from the Entity class.");
    public:
        /* returns a unordered map based on the input selection from the available sources */
        static std::unordered_map<int, std::shared_ptr<SelectableType>> getSelectablesFromInput(const std::string& selectionTitle, const std::unordered_map<int, std::shared_ptr<SelectableType>>& availableSelectables);
        /* returns a pointer based on the selection from an available source */
        static std::shared_ptr<SelectableType> getSelectableFromInput(const std::string& selectionTitle, const std::unordered_map<int, std::shared_ptr<SelectableType>>& availableSelectables);
        /* prints the selectables as a option based prompt */
        static void printSelectablesAsOptions(const std::unordered_map<int, std::shared_ptr<SelectableType>>& selectables);
        /* prints the selectables in a generic way */
        static void printSelectables(const std::unordered_map<int, std::shared_ptr<SelectableType>>& selectables);
        static void printSelectables(const std::vector<std::shared_ptr<SelectableType>>& selectables);
        static void printSelectables(const std::vector<SelectableType>& selectables);

        forType() = delete;
        ~forType() = delete;
    };

    /* compiler error if a initialization of this class is made */
    Prompt() = delete;
    ~Prompt() = delete;
};

#endif
