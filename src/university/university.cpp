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
#include<fstream>


const Map<int, String> University::mainMenuOptions = {
    { 0, "Exit;" },
    { 1, "Registration Menu;" },
    { 2, "Reports Menu;" },
    { 3, "Registration to Events Menu. " },
    { 4, "Generate log file from university data. " }
};

const Map<int, String> University::reportsMenuOptions = {
    { 0, "Exit;"},
    { 1, "Print Professors;" },
    { 2, "Print Students;" },
    { 3, "Print Subjects;" },
    { 4, "Print Workshop Events;" },
    { 5, "Print Lecture Events;" },
    { 6, "Print Fair Events;" },
    { 7, "Print Course Events;" },
    { 8, "Print all University Data." }
};

const Map<int, String> University::registrationsMenuOptions = {
    { 0, "Exit;"},
    { 1, "Register a Professor;" },
    { 2, "Register a Student;" },
    { 3, "Register a Subject;" },
    { 4, "Register a Workshop Event;" },
    { 5, "Register a Lecture Event;" },
    { 6, "Register a Fair Event;" },
    { 7, "Register a Course Event." }
};

const Map<int, String> University::eventRegistrationsMenuOptions = {
    { 0, "Exit;"},
    { 1, "Register Attendee to a Workshop;" },
    { 2, "Register Guest to a Workshop;" },
    { 3, "Register Attendee to Lecture;" },
    { 4, "Register Presenter to Fair;" },
    { 5, "Register Attendee to Fair;" },
    { 6, "Register Attendee to Course." }
};

// Simply prints all the university contents
void University::printSelf() const {
    Prompt::clearScreen();

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

void University::printProfessors() const {
    University::genericPrinter<ProfessorParticipant>("PROFESSORS", this->professors);
}
void University::printStudents() const {
    University::genericPrinter<StudentParticipant>("STUDENTS", this->students);
}

void University::printSubjects() const {
    University::genericPrinter<Subject>("SUBJECTS", this->subjects);
}



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
    if (!professor->isValid()) return false;
    return this->professors.insert(std::make_pair(professor->getId(), professor)).second;
}

bool University::registerStudent() {
    std::shared_ptr<StudentParticipant> student = std::make_shared<StudentParticipant>(this->subjects);
    if (!student->isValid()) return false;
    return this->students.insert(std::make_pair(student->getId(), student)).second;
}

bool University::registerSubject() {
    std::shared_ptr<Subject> subject = std::make_shared<Subject>();
    return this->subjects.insert(std::make_pair(subject->getId(), subject)).second;
}

bool University::registerWorkshop() {
    std::shared_ptr<WorkshopEvent> workshop = std::make_shared<WorkshopEvent>(this->subjects, this->professors);
    if (!workshop->isValid()) return false;
    return this->workshops.insert(std::make_pair(workshop->getId(), workshop)).second;
}

bool University::registerLecture() {
    std::shared_ptr<LectureEvent> lecture = std::make_shared<LectureEvent>(this->subjects, this->professors);
    if (!lecture->isValid()) return false;
    return this->lectures.insert(std::make_pair(lecture->getId(), lecture)).second;
}

bool University::registerFair() {
    std::shared_ptr<FairEvent> fair = std::make_shared<FairEvent>();
    if (!fair->isValid()) return false;
    return this->fairs.insert(std::make_pair(fair->getId(), fair)).second;
}

bool University::registerCourse() {
    std::shared_ptr<CourseEvent> course = std::make_shared<CourseEvent>(this->subjects, this->professors);
    if (!course->isValid()) return false;
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
            std::make_shared<InPersonEventRegistration<ExternalParticipant>>(std::make_shared<ExternalParticipant>()));

    return toRegisterWorkshop->
    addGuestRegistration(std::make_shared<OnlineEventRegistration<ExternalParticipant>>(std::make_shared<ExternalParticipant>()));
}

// Lecture
bool University::registerAttendeeToLecture() {
    std::shared_ptr<LectureEvent> toRegisterLecture =
    Prompt::forType<LectureEvent>::getSelectableFromInput("Select the lecture you want to add a attendee registration to.", this->lectures);
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
    std::shared_ptr<FairEvent> toRegisterFair =
    Prompt::forType<FairEvent>::getSelectableFromInput("Select the fair you want to add a presenter registration to.", this->fairs);
    bool inPerson = Prompt::getFlagFromInput("Will the presenter come in person to the event?");

    std::unordered_map<int, std::shared_ptr<StudentParticipant>> availableStudents = this->students;
    for (const int key : toRegisterFair->getPresentersKeys())
        availableStudents.erase(key);

    if (inPerson)
        return toRegisterFair->
            addPresenterRegistration(
                std::make_shared<InPersonEventRegistration<StudentParticipant>>(availableStudents));
    return toRegisterFair->
        addPresenterRegistration(std::make_shared<OnlineEventRegistration<StudentParticipant>>(availableStudents));
}

bool University::registerAttendeeToFair() {
    std::shared_ptr<FairEvent> toRegisterFair = Prompt::forType<FairEvent>::getSelectableFromInput("Select the fair you want to add a presenter registration to.", this->fairs);
    bool inPerson = Prompt::getFlagFromInput("Will the attendee come in person to the event?");

    if (inPerson)
        return toRegisterFair->addAttendeeRegistration(std::make_shared<InPersonEventRegistration<ExternalParticipant>>(std::make_shared<ExternalParticipant>()));
    
    return toRegisterFair->addAttendeeRegistration(std::make_shared<OnlineEventRegistration<ExternalParticipant>>(std::make_shared<ExternalParticipant>()));
}

// Course
bool University::registerAttendeeToCourse() {
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


Json University::serializeSelf() const {
    Json json = NamedEntity::serializeSelf();

    Json json_pparray = Json::array();
    Json json_sparray = Json::array();
    Json json_sarray = Json::array();
    Json json_wearray = Json::array();
    Json json_learray = Json::array();
    Json json_fearray = Json::array();
    Json json_cearray = Json::array();

    for (const auto& pair : this->professors)
        json_pparray.push_back({
            { "professor", pair.second->serializeSelf() }
        });

    for (const auto& pair : this->students)
        json_sparray.push_back({
            { "student", pair.second->serializeSelf() }
        });

    for (const auto& pair : this->subjects)
        json_sarray.push_back({
            { "subject", pair.second->serializeSelf() }
        });

    for (const auto& pair : this->workshops)
        json_wearray.push_back({
            { "workshop", pair.second->serializeSelf() }
        });

    for (const auto& pair : this->lectures)
        json_learray.push_back({
            { "lecture", pair.second->serializeSelf() }
        });

    for (const auto& pair : this->fairs)
        json_fearray.push_back({
            { "fair", pair.second->serializeSelf() }
        });

    for (const auto& pair : this->courses)
        json_cearray.push_back({
            { "course", pair.second->serializeSelf() }
        });

    json["professors"] = json_pparray;
    json["students"] = json_sparray;
    json["subjects"] = json_sarray;
    json["workshops"] = json_wearray;
    json["lectures"] = json_learray;
    json["fairs"] = json_fearray;
    json["courses"] = json_cearray;

    return json;
}

bool University::generateLogFile() const {
    std::ofstream file("university.json");

    if (file.is_open()) {
        file << this->serializeSelf().dump(4);
        file.close();
        return true;
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
        std::cout << "Couldn't open the file for writing..." << std::endl;
        return false;
    }
}
