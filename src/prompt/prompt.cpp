#include"prompt.h"

#include"subject.h"
#include"participant.h"
#include"student_participant.h"
#include"external_participant.h"
#include"professor_participant.h"
#include"event_base.h"
#include"fair_event.h"
#include"course_event.h"
#include"workshop_event.h"
#include"lecture_event.h"

#include<memory>
#include<unordered_map>
#include<iostream>
#include<limits>
#include<vector>

template<typename SelectableType>
std::shared_ptr<SelectableType> Prompt::forType<SelectableType>::getSelectableFromInput(const std::string& selectionTitle, const std::unordered_map<int, std::shared_ptr<SelectableType>>& availableSelectables) {
    std::shared_ptr<SelectableType> selected = nullptr;
    int input = -1;

    std::cout << selectionTitle;

    /* Available options */
    Prompt::forType<SelectableType>::printSelectablesAsOptions(availableSelectables);

    while (input != 0) {
        /* user selection */
        std::cout << "Enter a selection [0 to skip it]: ";
        std::cin >> input;

        if (input == 0) break;
        else input -= 1;

        /* If parsing fails or it isn't an option */
        if (std::cin.fail() || availableSelectables.find(input) == availableSelectables.end()) {
            std::cin.clear();
            /* clears any invalid input */
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid selection..." << std::endl;
            input = -1;
        } else {
            selected = availableSelectables.at(input);
            break;
        }
    }

    return selected;
}

template<typename SelectableType>
std::unordered_map<int, std::shared_ptr<SelectableType>> Prompt::forType<SelectableType>::getSelectablesFromInput(const std::string& selectionTitle, const std::unordered_map<int, std::shared_ptr<SelectableType>>& availableSelectables) {
    std::unordered_map<int, std::shared_ptr<SelectableType>> selected;
    int input = -1;

    std::cout << selectionTitle << std::endl;

    while (input != 0) {
        /* Available options */
        std::cout << "Currently available:" << std::endl;
        Prompt::forType<SelectableType>::printSelectablesAsOptions(availableSelectables);

        /* Currently selected */
        std::cout << "Currently selected:" << std::endl;
        Prompt::forType<SelectableType>::printSelectablesAsOptions(selected);

        /* user selection */
        std::cout << "Enter a selection ['0' exits]: ";
        std::cin >> input;

        if (input == 0) break;
        else input -= 1;

        /* If parsing fails or it isn't an option */
        if (std::cin.fail() || availableSelectables.find(input) == availableSelectables.end() || selected.find(input) != selected.end()) {
            std::cin.clear();
            /* clears any invalid input */
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid selection..." << std::endl;
            input = -1;
            continue;
        }

        /* Extracts and continues with the selection */
        selected.insert(std::make_pair(input, availableSelectables.at(input)));
        std::cout << std::endl << std::endl << "----------" << std::endl << "Next Selection:" << std::endl;
    }

    // in plain old c this would not work, but since
    // there is RVO - return value optimization - it will.
    return selected;
}

template<typename SelectableType>
void Prompt::forType<SelectableType>::printSelectablesAsOptions(const std::unordered_map<int, std::shared_ptr<SelectableType>>& selectables) {
    for (typename std::unordered_map<int, std::shared_ptr<SelectableType>>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        std::cout << "Option " << (*itr).first + 1 << ":" << std::endl;
        (*itr).second->printSelf();
    }
}

template<typename SelectableType>
void Prompt::forType<SelectableType>::printSelectables(const std::unordered_map<int, std::shared_ptr<SelectableType>>& selectables) {
    std::cout << std::endl;
    for (typename std::unordered_map<int, std::shared_ptr<SelectableType>>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        Prompt::printFullSeparator();
        (*itr).second->printSelf();
        Prompt::printFullSeparator();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename SelectableType>
void Prompt::forType<SelectableType>::printSelectables(const std::vector<SelectableType>& selectables) {
    std::cout << std::endl;
    for (typename std::vector<SelectableType>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        Prompt::printFullSeparator();
        (*itr).printSelf();
        Prompt::printFullSeparator();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename SelectableType>
void Prompt::forType<SelectableType>::printSelectables(const std::vector<std::shared_ptr<SelectableType>>& selectables) {
    Prompt::printFullSeparator();
    std::cout << std::endl;
    for (typename std::vector<std::shared_ptr<SelectableType>>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        Prompt::printFullSeparator();
        (*itr)->printSelf();
        std::cout << std::endl;
    }
    Prompt::printFullSeparator();
    std::cout << std::endl;

}

/* gets text from user */
std::string Prompt::getTextFromInput(const std::string& title) {
    std::cout << title << std::endl;
    std::string text;
    std::cin >> text;
    return text;
}

int Prompt::getIntFromInput(const std::string& title) {
    int intValue;
    std::cout << title << std::endl;
    while(!(std::cin >> intValue)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid int value..." << std::endl;
    }
    return intValue;
}

/* gets a boolean option from the user */
bool Prompt::getFlagFromInput(const std::string& title) {
    int input = -1;
    std::cout << title << std::endl;
    while (input == -1) {
        std::cout << "[1]: yes" << std::endl;
        std::cout << "[0]: no" << std::endl;
        std::cout << "Your answer: ";
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid selection..." << std::endl;
            input = -1;
        }
    }
    return input == 1;
}

void Prompt::printFullSeparator() {
    std::cout << "-------------" << std::endl;
}

void Prompt::printPartialSeparator() {
    std::cout << "-----" << std::endl;
}

void Prompt::printHugeSeparator() {
    std::cout << "------------------" << std::endl;
}

template class Prompt::forType<Subject>;
template class Prompt::forType<Participant>;
template class Prompt::forType<StudentParticipant>;
template class Prompt::forType<ExternalParticipant>;
template class Prompt::forType<ProfessorParticipant>;
template class Prompt::forType<EventBase>;
template class Prompt::forType<WorkshopEvent>;
template class Prompt::forType<LectureEvent>;
template class Prompt::forType<FairEvent>;
template class Prompt::forType<CourseEvent>;
