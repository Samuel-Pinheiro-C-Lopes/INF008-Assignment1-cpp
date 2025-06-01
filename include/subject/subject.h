#ifndef SUBJECT_H
#define SUBJECT_H

#include"entity.h"

#include<unordered_map>
#include<memory>

class Subject : public Entity {
public:
    /* base fill from input constructor */
    Subject() : Entity(nextId()) {}
    Subject(std::string name) : Entity(nextId(), name) {};
    /* Prints the subjects in a option based menu */
    static void printSubjectsAsOptions(const std::unordered_map<int, std::shared_ptr<Subject>>& subjects);
    /* Receives subjects from user input based on a selection
     * from the options provided, returning it */
    static std::unordered_map<int, std::shared_ptr<Subject>> selectSubjectsFromInput(const std::string& selectionTitle, const std::unordered_map<int, std::shared_ptr<Subject>>& availableSubjects);
protected:
    int nextId() override;
    static int currentId;
};

#endif
