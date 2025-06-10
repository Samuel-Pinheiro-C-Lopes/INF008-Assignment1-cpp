#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include"named_entity.h"

#include"professor_participant.h"
#include"student_participant.h"

#include"subject.h"

#include"workshop_event.h"
#include"lecture_event.h"
#include"fair_event.h"
#include"course_event.h"

#include"data_gen.h"

#include<unordered_map>
#include<memory>
#include<vector>
#include<type_traits>
#include<iostream>
#include<type_traits>

class University : public NamedEntity {
public:
    University(std::string name) : NamedEntity(nextId(), name) {};
    University() : NamedEntity(nextId()) {};
    void printSelf() const override;

    /* Prints. Probably only need to use generalization of Prompt::forType<type>::printAll(const unordered_map<int, std::shared_ptr<type>> mapToPrint). */
    void printProfessors() const;
    void printStudents() const;

    void printSubjects() const;

    void printEventsByMonth(const int month);
    void printWorkshops() const;
    void printLectures() const;
    void printFairs() const;
    void printCourses() const;

    /* University registrations. Probably will only need to call the empty constructor of everyone
     * with the available choices. */
    bool registerProfessor();
    bool registerStudent();

    bool registerSubject();

    bool registerWorkshop();
    bool registerLecture();
    bool registerFair();
    bool registerCourse();

    /* Specific events registrations. */

    // Workshop
    bool registerAttendeeToWorkshop();
    bool registerGuestToWorkshop();
    // Lecture
    bool registerAttendeeToToLecture();
    // Fair
    bool registerPresenterToFair();
    bool registerAttendeeToToFair();
    // Course
    bool registerAttendeToCourse();

private:
    int nextId() override { return 0; }

    std::unordered_map<int, std::shared_ptr<ProfessorParticipant>> professors;
    std::unordered_map<int, std::shared_ptr<StudentParticipant>> students;

    std::unordered_map<int, std::shared_ptr<Subject>> subjects;

    std::unordered_map<int, std::shared_ptr<WorkshopEvent>> workshops;
    std::unordered_map<int, std::shared_ptr<LectureEvent>> lectures;
    std::unordered_map<int, std::shared_ptr<FairEvent>> fairs;
    std::unordered_map<int, std::shared_ptr<CourseEvent>> courses;


    template<typename EventTargetType, typename EventSourceType>
    void pushBackEventsByMonthTo(std::vector<std::shared_ptr<EventTargetType>> target, std::unordered_map<int, std::shared_ptr<EventSourceType>> source, int month) {
        static_assert(std::is_base_of<EventBase, EventTargetType>::value, "<EventTargetType> of pushBackEventsByMonthTo([...]) must be derived from EventBase class");
        static_assert(std::is_base_of<EventTargetType, EventSourceType>::value, "<EventSourceType> of pushBackEventsByMonthTo([...]) must be derived from EventTargetType class");

        for (const std::pair<int, std::shared_ptr<EventSourceType>> pair : source)
            if (pair.second->getDate().getMonth() == month)
                target.push_back(pair.second);
    };

    template<typename whatToPrintType>
    static void genericPrinter(const std::string& whatToPrint, const std::unordered_map<int, std::shared_ptr<whatToPrintType>>& sourceToPrintFrom) {
        static_assert(std::is_base_of<Entity, whatToPrintType>::value, "<whatToPrintType> of University::genericPrinter([...]) must be derived from Entity class");
        Prompt::printHugeSeparator();
        std::cout << whatToPrint << " CURRENTLY REGISTERED: " << std::endl;
        Prompt::printHugeSeparator();
        Prompt::forType<whatToPrintType>::printSelectables(sourceToPrintFrom);
    }

    // so that the data gen can actually work with an university and fill it
    friend class DataGen;
};

#endif
