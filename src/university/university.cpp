#include"university.h"

#include"named_entity.h"

#include"professor_participant.h"
#include"student_participant.h"

#include"subject.h"

#include"workshop_event.h"
#include"lecture_event.h"
#include"fair_event.h"
#include"course_event.h"

#include"prompt.h"
#include"event.h"
#include"event_base.h"

#include"data_gen.h"

#include<unordered_map>
#include<memory>
#include<iostream>

// Simply prints all the university contents
void University::printSelf() const {
    // header
    Prompt::printFullSeparator();
    std::cout << "UNIVERSITY: ";
    NamedEntity::printSelf();
    std::cout << std::endl;

    // professors
    University::genericPrinter<ProfessorParticipant>("PROFESSORS", this->professors);

    // students
    University::genericPrinter<StudentParticipant>("STUDENTS", this->students);

    // Subjects
    University::genericPrinter<Subject>("SUBJECTS", this->subjects);

    // workshops
    University::genericPrinter<WorkshopEvent>("WORKSHOPS", this->workshops);

    // lectures
    University::genericPrinter<LectureEvent>("LECTURES", this->lectures);

    // fairs
    University::genericPrinter<FairEvent>("FAIRS", this->fairs);

    // courses
    University::genericPrinter<CourseEvent>("COURSES", this->courses);

    Prompt::printFullSeparator();
}


// Prints. Probably only need to use generalization of Prompt::forType<type>::printAll(const unordered_map<int, std::shared_ptr<type>> mapToPrint).
/*
void University::printProfessors() const {
    std::cout << "PROFESSORS currently registered: "
    << std::endl << "-----------------------" << std::endl;
    Prompt::forType<ProfessorParticipant>::printSelectables(this->professors);
    std::cout << "-----------------------" << std::endl;
}
void University::printStudents() const {
    std::cout << "STUDENTS currently registered: "
    << std::endl << "-----------------------" << std::endl;
    Prompt::forType<StudentParticipant>::printSelectables(this->students);
    std::cout << "-----------------------" << std::endl;
}

void University::printSubjects() const {
    std::cout << "SUBJECTS currently registered: "
    << std::endl << "-----------------------" << std::endl;
    Prompt::forType<Subject>::printSelectables(this->subjects);
    std::cout << "-----------------------" << std::endl;
}
*/


void University::printEventsByMonth(const int month) {
    std::vector<std::shared_ptr<EventBase>> events;

    University::pushBackEventsByMonthTo<EventBase, WorkshopEvent>(events, this->workshops, month);
    University::pushBackEventsByMonthTo<EventBase, LectureEvent>(events, this->lectures, month);
    University::pushBackEventsByMonthTo<EventBase, FairEvent>(events, this->fairs, month);
    University::pushBackEventsByMonthTo<EventBase, CourseEvent>(events, this->courses, month);

    Prompt::forType<EventBase>::printSelectables(events);
}

void University::printWorkshops() const {
    std::cout << "WORKSHOPS currently registered: "
    << std::endl << "-----------------------" << std::endl;
    Prompt::forType<WorkshopEvent>::printSelectables(this->workshops);
    std::cout << "-----------------------" << std::endl;
}

void University::printLectures() const {
    std::cout << "Lectures currently registered in the university: " << std::endl;
    Prompt::template forType<LectureEvent>::printSelectables(this->lectures);
}

void University::printFairs() const {
    std::cout << "Fairs currently registered in the university: " << std::endl;
    Prompt::template forType<FairEvent>::printSelectables(this->fairs);
}

void University::printCourses() const {
    std::cout << "Courses currently registered in the university: " << std::endl;
    Prompt::template forType<CourseEvent>::printSelectables(this->courses);
}

// University registrations. Probably will only need to call the empty constructor of everyone with the available choices.
void University::registerProfessor() {
    std::shared_ptr<ProfessorParticipant> professor = std::make_shared<ProfessorParticipant>(this->subjects);
    this->professors.insert(std::make_pair(professor->getId(), professor));
}

void University::registerStudent() {
    std::shared_ptr<StudentParticipant> student = std::make_shared<StudentParticipant>(this->subjects);
    this->students.insert(std::make_pair(student->getId(), student));
}

void University::registerSubject() {
    std::shared_ptr<Subject> subject = std::make_shared<Subject>();
    this->subjects.insert(std::make_pair(subject->getId(), subject));
}

void University::registerWorkshop() {
    std::shared_ptr<WorkshopEvent> workshop = std::make_shared<WorkshopEvent>(this->subjects, this->professors);
    this->workshops.insert(std::make_pair(workshop->getId(), workshop));
}

void University::registerLecture() {
    std::shared_ptr<LectureEvent> lecture = std::make_shared<LectureEvent>(this->subjects, this->professors);
    this->lectures.insert(std::make_pair(lecture->getId(), lecture));
}

void University::registerFair() {
    std::shared_ptr<FairEvent> fair = std::make_shared<FairEvent>();
    this->fairs.insert(std::make_pair(fair->getId(), fair));
}

void University::registerCourse() {
    std::shared_ptr<CourseEvent> course = std::make_shared<CourseEvent>(this->subjects, this->professors);
    this->courses.insert(std::make_pair(course->getId(), course));
}




/*
University::University(bool test): NamedEntity(nextId(), "Test University") {
    // participants
    this->professors = DataGen::generateProfessorData();
    this->students = DataGen::generateStudentData();
    this->subjects = DataGen::generateSubjectData();

    // events
    this->workshops = DataGen::generateWorkshopData();
    this->lectures = DataGen::generateLectureData();
    this->fairs = DataGen::generateFairData();
    this->courses = DataGen::generateCourseData();

    // participants in person registrations towards the events
    std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<StudentParticipant>>> studentsInPersonRegistrations = DataGen::generateInPersonStudentRegistrationData();
    std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<ProfessorParticipant>>> professorsInPersonRegistrations = DataGen::generateInPersonProfessorRegistrationData();
    std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<ExternalParticipant>>> externalsInPersonRegistrations = DataGen::generateInPersonExternalRegistrationData();

    // participants online registrations towarss the events
    std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<StudentParticipant>>> studentsOnlineRegistrations = DataGen::generateOnlineStudentRegistrationData();
    std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<ProfessorParticipant>>> professorsOnlineRegistrations = DataGen::generateOnlineProfessorRegistrationData();
    std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<ExternalParticipant>>> externalsOnlineRegistrations = DataGen::generateOnlineExternalRegistrationData();

    // now let's register them...

}
*/
