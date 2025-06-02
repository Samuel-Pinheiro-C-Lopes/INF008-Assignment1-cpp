#ifndef PROMPT_H
#define PROMPT_H

#include"entity.h"

#include<memory>
#include<type_traits>
#include<unordered_map>

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

        forType() = delete;
        ~forType() = delete;
    };

    /* compiler error if a initialization of this class is made */
    Prompt() = delete;
    ~Prompt() = delete;
};

#endif
