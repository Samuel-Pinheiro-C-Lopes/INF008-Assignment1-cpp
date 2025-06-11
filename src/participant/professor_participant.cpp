#include"professor_participant.h"

#include"subject.h"
#include"prompt.h"

#include<memory>
#include<unordered_map>
#include<iostream>
#include<limits>

/* Default id sequence */
int ProfessorParticipant::currentId = 1;
int ProfessorParticipant::nextId() {
    return ProfessorParticipant::currentId++;
}

void ProfessorParticipant::printSelf() const {
    std::cout << "Professor name: ";
    Participant::printSelf();

    std::cout << "Currently teaching the following subjects: " << std::endl;
    for (const std::pair<int, Ptr<Subject>>& pair : this->teachingSubjects)
        pair.second->printSelf();
}

bool ProfessorParticipant::teaches(
    const Ptr<Subject>& subject
) const {
    return this->teachingSubjects.find(subject->getId()) != this->teachingSubjects.end();
}

bool ProfessorParticipant::addSubject(
    const Ptr<Subject>& subject
) {
    return this->teachingSubjects.insert(std::make_pair(subject->getId(), subject)).second;
}

Json ProfessorParticipant::serializeSelf() const {
    Json json = Participant::serializeSelf();
    Json json_array = Json::array();

    for (const std::pair<int, Ptr<Subject>>& pair : this->teachingSubjects)
        json_array.push_back({
            { "subject", pair.second->getId() }
        });

    json["subjects"] = json_array;

    return json;
}




/*
 Based on a source of available subjects, let's the user select uniquely for the professor
 deprecated since assigning this logic to the subject would be better for reusability
std::unordered_map<int, Ptr<Subject>> ProfessorParticipant::teachingSubjectsFromInput(const std::unordered_map<int, Ptr<Subject>>& availableSubjects) {
    std::unordered_map<int, Ptr<Subject>> selectedSubjects;
    int input = -1;

    while (input != 0) {

        Subject::printSubjectsAsOptions(availableSubjects);


        std::cout << "Currently selected:" << std::endl;
        Subject::printSubjectsAsOptions(selectedSubjects);


        std::cout << "Enter a selection ['0' exits]: ";
        std::cin >> input;


        if (std::cin.fail() || availableSubjects.find(input) == availableSubjects.end() || selectedSubjects.find(input) != selectedSubjects.end()) {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a valid selection..." << std::endl;
            input = -1;
            continue;
        }


        if (input != 0)
            selectedSubjects.insert(std::make_pair(input, availableSubjects.at(input)));
        std::cout << std::endl << std::endl << "----------" << std::endl << "Next Selection:" << std::endl;
    }

    // in plain old c this would not work, but since
    // there is RVO - return value optimization - it will.
    return selectedSubjects;
}
*/
