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

#include"alias.h"

#include<iostream>
#include<limits>

using namespace alias;

template<typename T>
Ptr<T> Prompt::forType<T>::getSelectableFromInput(
    const String& selectionTitle,
    const Map<int,Ptr<T>>& availableSelectables
) {
    Ptr<T> selected = nullptr;
    int input = -1;

    std::cout << selectionTitle << std::endl;

    /* Available options */
    Prompt::forType<T>::printSelectablesAsOptions(availableSelectables);

    while (input != 0) {
        /* user selection */
        std::cout << "Enter a selection [0 to skip it]: ";

        /* If parsing fails or it isn't an option */
        if (!Prompt::forType<T>::handleLastCinInput(input, availableSelectables) && input != 0) {
            continue;
        } else {
            if (input != 0)
                selected = availableSelectables.at(input);
            break;
        }
    }

    return selected;
}

template<typename T>
Map<int, Ptr<T>> Prompt::forType<T>::getSelectablesFromInput(
    const String& selectionTitle,
    const Map<int, Ptr<T>>& availableSelectables
) {
    Map<int, Ptr<T>> currentAvailable = availableSelectables;
    Map<int, Ptr<T>> currentSelected;
    int input = -1;

    std::cout << selectionTitle << std::endl;

    while (input != 0) {
        /* Available options */
        std::cout << "Currently available:" << std::endl;
        Prompt::forType<T>::printSelectablesAsOptions(currentAvailable);

        Prompt::printPartialSeparator();

        /* Currently selected */
        std::cout << "Currently selected:" << std::endl;
        Prompt::forType<T>::printSelectablesAsOptions(currentSelected);

        Prompt::printPartialSeparator();

        /* user selection */
        std::cout << "Enter a selection ['0' finishes]: ";

        if (!Prompt::forType<T>::handleLastCinInput(input, currentAvailable, currentSelected))
            continue;

        if (input == 0)
            break;

        currentSelected[input] = std::move(currentAvailable[input]);
        currentAvailable.erase(input);
        // currentSelected.insert(currentAvailable.extract(input)); // above adopted to be friendly toward older c++ compilers
        std::cout << std::endl << std::endl << "----------" << std::endl << "Next Selection:" << std::endl;
    }

    // in plain old c this would not work, but since
    // there is RVO - return value optimization - it will.
    return currentSelected;
}

template<typename T>
void Prompt::forType<T>::printSelectablesAsOptions(
    const Map<int, Ptr<T>>& selectables
) {
    for (typename Map<int, Ptr<T>>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        std::cout << "Option [" << (*itr).first << "]: " << std::endl;
        (*itr).second->printSelf();
    }
}

void Prompt::printSelectablesAsOptions(
    const Map<int, String>& selectables
) {
    for (Map<int, String>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        std::cout << "Option [" << (*itr).first << "]: " << (*itr).second << std::endl;
    }
}

template<typename T>
void Prompt::forType<T>::printSelectables(
    const Map<int, Ptr<T>>& selectables
) {
    std::cout << std::endl;
    for (typename Map<int, Ptr<T>>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        Prompt::printFullSeparator();
        (*itr).second->printSelf();
        Prompt::printFullSeparator();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename T>
void Prompt::forType<T>::printSelectables(
    const Vector<T>& selectables
) {
    std::cout << std::endl;
    for (typename Vector<T>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        Prompt::printFullSeparator();
        (*itr).printSelf();
        Prompt::printFullSeparator();
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<typename T>
void Prompt::forType<T>::printSelectables(
    const Vector<Ptr<T>>& selectables
) {
    Prompt::printFullSeparator();
    std::cout << std::endl;
    for (typename Vector<Ptr<T>>::const_iterator itr = selectables.begin(); itr != selectables.end(); ++itr) {
        Prompt::printFullSeparator();
        (*itr)->printSelf();
        std::cout << std::endl;
    }
    Prompt::printFullSeparator();
    std::cout << std::endl;

}

// SIMPLE GETTERS FROM INPUT

/* gets text from user */
std::string Prompt::getTextFromInput(
    const std::string& title
) {
    std::cout << title << std::endl;
    std::string text;

    if (std::cin.peek() == '\n') {
        // discard leftover newline if it's sitting in the buffer
        std::cin.ignore(1, '\n');
    }

    std::getline(std::cin, text);
    return text;
}

/* gets int from input */
int Prompt::getIntFromInput(
    const std::string& title
) {
    int intValue;
    std::cout << title << std::endl;

    while(!Prompt::handleLastCinInput(intValue));

    return intValue;
}

/* gets a boolean option from the user */
bool Prompt::getFlagFromInput(
    const std::string& title
) {
    int input = -1;

    std::cout << title << std::endl;
    std::cout << "[1]: yes" << std::endl;
    std::cout << "[0]: no" << std::endl;
    std::cout << "Your answer: ";

    while (!Prompt::handleLastCinInput(input, 0, 1));

    return input == 1;
}

// SIMPLE GETTERS FROM INPUT

// SEPARATORS

void Prompt::printFullSeparator() {
    std::cout << "-------------" << std::endl;
}

void Prompt::printPartialSeparator() {
    std::cout << "-----" << std::endl;
}

void Prompt::printHugeSeparator() {
    std::cout << "------------------" << std::endl;
}

// SEPARATORS

int Prompt::getOptionFromInput(
    const Map<int, String>& options
) {
    int input = -1;

    while (input == -1) {
        std::cout << "Options Available:" << std::endl;
        Prompt::printSelectablesAsOptions(options);
        if (!Prompt::handleLastCinInput(input, options))
            continue;
    }

    return input;
}

template<typename T>
bool Prompt::forType<T>::handleLastCinInput(
    int& input,
    const Map<int, Ptr<T>>& options
) {
    int snapshot = input;
    /* If parsing fails or it isn't an option */
    if (!(std::cin >> input) || options.find(input) == options.end()) {
        std::cin.clear();
        /* clears any invalid input */
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input. Please try again." << std::endl;
        std::cout << "Please enter with a valid option between the ones provided!" << std::endl;
        input = snapshot;
        return false;
    }

    return true;
}

bool Prompt::handleLastCinInput(
    int& input,
    const int rangeStart,
    const int rangeEnd
) {
    /* If parsing fails or it isn't in range */
    int snapshot = input;
    if (!(std::cin >> input) || input > rangeEnd || input < rangeStart) {
        std::cin.clear();
        /* clears any invalid input */
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input. Please try again." << std::endl;
        std::cout << "Please enter a valid option between " << rangeStart << " and " << rangeEnd << "." << std::endl;
        input = snapshot;
        return false;
    }

    return true;
}

template<typename T>
bool Prompt::forType<T>::handleLastCinInput(
    int& input,
    const Map<int, Ptr<T>>& options,
    const Map<int, Ptr<T>>& alreadySelectedOptions
) {
    int snapshot = input;
    /* If parsing fails, it isn't present in the available or is already selected */
    if ((!(std::cin >> input) || options.find(input) == options.end() || alreadySelectedOptions.find(input) != alreadySelectedOptions.end()) && input != 0) {
        std::cin.clear();
        /* clears any invalid input */
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input. Please try again." << std::endl;
        std::cout << "Please enter with a valid option between the ones provided!" << std::endl;
        input = snapshot;
        return false;
    }

    return true;
}

bool Prompt::handleLastCinInput(
    int& input
) {
    int snapshot = input;
    int intValue;

    if(!(std::cin >> intValue)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please enter a valid int value..." << std::endl;
        return false;
    }

    return true;
}

bool Prompt::handleLastCinInput(
    int& input,
    const Map<int, String>& options
) {
    int snapshot = input;

    /* If parsing fails or it isn't an option */
    if (!(std::cin >> input) || options.find(input) == options.end()) {
        std::cin.clear();
        /* clears any invalid input */
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid input. Please try again." << std::endl;
        std::cout << "Please enter with a valid option between the ones provided!" << std::endl;
        input = snapshot;
        return false;
    }

    return true;
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
