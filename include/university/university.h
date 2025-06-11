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

#include"alias.h"

#include<unordered_map>
#include<memory>
#include<vector>
#include<type_traits>
#include<iostream>
#include<type_traits>

using namespace alias;

class University : public NamedEntity {
public:
    University(
        String name
    ) : NamedEntity(nextId(), name) {};

    University() : NamedEntity(nextId()) {};

    static const Map<int, String> mainMenuOptions;

    static const Map<int, String> reportsMenuOptions;

    static const Map<int, String> registrationsMenuOptions;

    static const Map<int, String> eventRegistrationsMenuOptions;

    void printSelf() const override;
    Json serializeSelf() const override;
    bool generateLogFile() const;

    /* Prints. */
    void printProfessors() const;
    void printStudents() const;

    void printSubjects() const;

    void printEventsByMonth(const int month);
    void printWorkshops() const;
    void printLectures() const;
    void printFairs() const;
    void printCourses() const;

    /* University registrations. */
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
    bool registerAttendeeToLecture();
    // Fair
    bool registerPresenterToFair();
    bool registerAttendeeToFair();
    // Course
    bool registerAttendeeToCourse();

private:
    int nextId() override { return 0; }

    Map<int, Ptr<ProfessorParticipant>> professors;
    Map<int, Ptr<StudentParticipant>> students;

    Map<int, Ptr<Subject>> subjects;

    Map<int, Ptr<WorkshopEvent>> workshops;
    Map<int, Ptr<LectureEvent>> lectures;
    Map<int, Ptr<FairEvent>> fairs;
    Map<int, Ptr<CourseEvent>> courses;


    template<typename T, typename G>
    void pushBackEventsByMonthTo(
        Vector<Ptr<T>>& target,
        Map<int, Ptr<G>> source,
        int month
    ) {
        static_assert(std::is_base_of<EventBase, T>::value, "<T> of pushBackEventsByMonthTo([...]) must be derived from EventBase class");
        static_assert(std::is_base_of<T, G>::value, "<G> of pushBackEventsByMonthTo([...]) must be derived from T class");

        for (const std::pair<int, Ptr<G>> pair : source)
            if (pair.second->getDate().getMonth() == month)
                target.push_back(pair.second);
    };

    template<typename T>
    static void genericPrinter(
        const String& whatToPrint,
        const Map<int, Ptr<T>>& sourceToPrintFrom
    ) {
        static_assert(std::is_base_of<Entity, T>::value, "<T> of University::genericPrinter([...]) must be derived from Entity class");

        std::cout << "┌────────────────────────────" << std::endl;
        std::cout << "│" << std::endl;
        //Prompt::printHugeSeparator();
        std::cout << "│" << whatToPrint << " CURRENTLY REGISTERED: " << std::endl
                  << "│" << std::endl
                  << "│" << "──────────────────────────────" << std::endl;
        //Prompt::printHugeSeparator();
        Prompt::forType<T>::printSelectables(sourceToPrintFrom);
        std::cout << "│" << std::endl;
        std::cout << "└────────────────────────────" << std::endl;
    }

    // so that the data gen can actually work with an university and fill it
    friend class DataGen;
};

#endif
