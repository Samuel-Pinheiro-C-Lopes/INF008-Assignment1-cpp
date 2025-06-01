#include"subject.h"

#include<iostream>
#include<unordered_map>
#include<memory>
#include<limits>

/* Default id sequence */
int Subject::currentId = 0;
int Subject::nextId() {
    return Subject::currentId++;
}

void Subject::printSubjectsAsOptions(const std::unordered_map<int, std::shared_ptr<Subject>>& subjects) {
    for (std::unordered_map<int, std::shared_ptr<Subject>>::const_iterator itr = subjects.begin(); itr != subjects.end(); ++itr) {
        std::cout << "Option " << (*itr).first << ":" << std::endl;
        (*itr).second->printSelf();
    }
}

/* Based on a source of available subjects, let's the user select */
std::unordered_map<int, std::shared_ptr<Subject>> Subject::selectSubjectsFromInput(const std::string& selectionTitle, const std::unordered_map<int, std::shared_ptr<Subject>>& availableSubjects) {
    std::unordered_map<int, std::shared_ptr<Subject>> selectedSubjects;
    int input = -1;

    std::cout << selectionTitle << std::endl;

    while (input != 0) {
        /* Available options */
        Subject::printSubjectsAsOptions(availableSubjects);

        /* Currently selected */
        std::cout << "Currently selected:" << std::endl;
        Subject::printSubjectsAsOptions(selectedSubjects);

        /* user selection */
        std::cout << "Enter a selection ['0' exits]: ";
        std::cin >> input;

        /* If parsing fails or it isn't an option */
        if (std::cin.fail() || availableSubjects.find(input) == availableSubjects.end() || selectedSubjects.find(input) != selectedSubjects.end()) {
            std::cin.clear();
            /* clears any invalid input */
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid selection..." << std::endl;
            input = -1;
            continue;
        }

        /* Extracts and continues with the selection */
        if (input != 0)
            selectedSubjects.insert(std::make_pair(input, availableSubjects.at(input)));
        std::cout << std::endl << std::endl << "----------" << std::endl << "Next Selection:" << std::endl;
    }

    // in plain old c this would not work, but since
    // there is RVO - return value optimization - it will.
    return selectedSubjects;
}
