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
    University::genericPrinter<WorkshopEvent>("WORKSHOPS", this->workshops);
}

void University::printLectures() const {
    University::genericPrinter<LectureEvent>("LECTURES", this->lectures);
}

void University::printFairs() const {
    University::genericPrinter<FairEvent>("FAIRS", this->fairs);
}

void University::printCourses() const {
    University::genericPrinter<CourseEvent>("COURSES", this->courses);
}

// University registrations. Probably will only need to call the empty constructor of everyone with the available choices.
bool University::registerProfessor() {
    std::shared_ptr<ProfessorParticipant> professor = std::make_shared<ProfessorParticipant>(this->subjects);
    return this->professors.insert(std::make_pair(professor->getId(), professor)).second;
}

bool University::registerStudent() {
    std::shared_ptr<StudentParticipant> student = std::make_shared<StudentParticipant>(this->subjects);
    return this->students.insert(std::make_pair(student->getId(), student)).second;
}

bool University::registerSubject() {
    std::shared_ptr<Subject> subject = std::make_shared<Subject>();
    return this->subjects.insert(std::make_pair(subject->getId(), subject)).second;
}

bool University::registerWorkshop() {
    std::shared_ptr<WorkshopEvent> workshop = std::make_shared<WorkshopEvent>(this->subjects, this->professors);
    return this->workshops.insert(std::make_pair(workshop->getId(), workshop)).second;
}

bool University::registerLecture() {
    std::shared_ptr<LectureEvent> lecture = std::make_shared<LectureEvent>(this->subjects, this->professors);
    return this->lectures.insert(std::make_pair(lecture->getId(), lecture)).second;
}

bool University::registerFair() {
    std::shared_ptr<FairEvent> fair = std::make_shared<FairEvent>();
    return this->fairs.insert(std::make_pair(fair->getId(), fair)).second;
}

bool University::registerCourse() {
    std::shared_ptr<CourseEvent> course = std::make_shared<CourseEvent>(this->subjects, this->professors);
    return this->courses.insert(std::make_pair(course->getId(), course)).second;
}



// Workshop
bool University::registerAttendeeToWorkshop() {
    std::shared_ptr<WorkshopEvent> toRegisterWorkshop =
    Prompt::forType<WorkshopEvent>::getSelectableFromInput("Select the workshop you want to add a attendee registration to.", this->workshops);
    bool inPerson = Prompt::getFlagFromInput("Will the participant come in person to the event?");

    std::unordered_map<int, std::shared_ptr<StudentParticipant>> availableStudents = this->students;

    for (const int key : toRegisterWorkshop->getAttendesKeys())
        availableStudents.erase(key);

    if (inPerson)
        return toRegisterWorkshop->
        addAttendeeRegistration(std::make_shared<InPersonEventRegistration<StudentParticipant>>(availableStudents));

    return toRegisterWorkshop->
        addAttendeeRegistration(std::make_shared<OnlineEventRegistration<StudentParticipant>>(availableStudents));
}


bool University::registerGuestToWorkshop() {
    std::shared_ptr<WorkshopEvent> toRegisterWorkshop =
    Prompt::forType<WorkshopEvent>::getSelectableFromInput("Select the workshop you want to add a guest registration to.", this->workshops);
    bool inPerson = Prompt::getFlagFromInput("Will the guest come in person to the event?");

    if (inPerson)
        return toRegisterWorkshop->
        addGuestRegistration(
            std::make_shared<InPersonEventRegistration<ExternalParticipant>>());

    return toRegisterWorkshop->
    addGuestRegistration(std::make_shared<OnlineEventRegistration<ExternalParticipant>>());
}

// Lecture
bool University::registerAttendeeToToLecture() {
    std::shared_ptr<LectureEvent> toRegisterLecture =
    Prompt::forType<LectureEvent>::getSelectableFromInput("Select the workshop you want to add a attendee registration to.", this->lectures);
    bool inPerson = Prompt::getFlagFromInput("Will the student come in person to the event?");

    std::unordered_map<int, std::shared_ptr<StudentParticipant>> availableStudents = this->students;

    for (const int key : toRegisterLecture->getAttendesKeys())
        availableStudents.erase(key);

    if (inPerson)
        return toRegisterLecture->
        addAttendeeRegistration(std::make_shared<InPersonEventRegistration<StudentParticipant>>(availableStudents));

    return toRegisterLecture->
    addAttendeeRegistration(std::make_shared<OnlineEventRegistration<StudentParticipant>>(availableStudents));
}

// Fair
bool University::registerPresenterToFair() {
    std::shared_ptr<WorkshopEvent> toRegisterWorkshop =
    Prompt::forType<WorkshopEvent>::getSelectableFromInput("Select the fair you want to add a guest registration to.", this->workshops);
    bool inPerson = Prompt::getFlagFromInput("Will the presenter come in person to the event?");

    if (inPerson)
        return toRegisterWorkshop->
        addGuestRegistration(
            std::make_shared<InPersonEventRegistration<ExternalParticipant>>());

        return toRegisterWorkshop->
        addGuestRegistration(std::make_shared<OnlineEventRegistration<ExternalParticipant>>());
}

bool University::registerAttendeeToToFair() {
    return false;
}

// Course
bool University::registerAttendeToCourse() {
    std::shared_ptr<CourseEvent> toRegisterCourse =
    Prompt::forType<CourseEvent>::getSelectableFromInput("Select the course you want to add a attendee registration to.", this->courses);
    bool inPerson = Prompt::getFlagFromInput("Will the student come in person to the event?");

    std::unordered_map<int, std::shared_ptr<StudentParticipant>> availableStudents = this->students;

    for (const int key : toRegisterCourse->getAttendesKeys())
        availableStudents.erase(key);

    if (inPerson)
        return toRegisterCourse->
        addAttendeeRegistration(std::make_shared<InPersonEventRegistration<StudentParticipant>>(availableStudents));

    return toRegisterCourse->
    addAttendeeRegistration(std::make_shared<OnlineEventRegistration<StudentParticipant>>(availableStudents));
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
