#include"data_gen.h"

#include"professor_participant.h"
#include"student_participant.h"

#include"subject.h"

#include"workshop_event.h"
#include"lecture_event.h"
#include"fair_event.h"
#include"course_event.h"

#include"in_person_event_registration.h"
#include"online_event_registration.h"

#include"university.h"

#include<memory>
#include<vector>
#include<unordered_map>
#include<string>
#include<iostream>

void DataGen::generateDataFor(University& university) {
    // generating subjects
    std::unordered_map<int, std::shared_ptr<Subject>> subjects;
    std::shared_ptr<Subject> currSubject;
    for (const std::string& name : {"Literature", "Soft Skills", "Database", "Web Development", "Design"}) {
        currSubject = std::make_shared<Subject>(name);
        subjects[currSubject->getId()] = currSubject;
    }
    university.subjects = subjects;

    // now the students
    std::unordered_map<int, std::shared_ptr<StudentParticipant>> students;
    std::shared_ptr<StudentParticipant> currStudent;
    std::unordered_map<int, std::shared_ptr<Subject>> learningSubjects;

    learningSubjects.insert(std::make_pair(1, university.subjects.at(1)));
    learningSubjects.insert(std::make_pair(2, university.subjects.at(2)));
    currStudent = std::make_shared<StudentParticipant>("Thomas Wayne", "002.371.457-31", learningSubjects);
    students.insert(std::make_pair(currStudent->getId(), currStudent));
    learningSubjects.clear();

    learningSubjects.insert(std::make_pair(2, university.subjects.at(2)));
    learningSubjects.insert(std::make_pair(3, university.subjects.at(3)));
    currStudent = std::make_shared<StudentParticipant>("Jeanne Oliver", "559.332.637-10", learningSubjects);
    students.insert(std::make_pair(currStudent->getId(), currStudent));
    learningSubjects.clear();

    learningSubjects.insert(std::make_pair(3, university.subjects.at(3)));
    currStudent = std::make_shared<StudentParticipant>("August IV", "921.111.916-20", learningSubjects);
    students.insert(std::make_pair(currStudent->getId(), currStudent));
    learningSubjects.clear();

    learningSubjects.insert(std::make_pair(1, university.subjects.at(1)));
    learningSubjects.insert(std::make_pair(2, university.subjects.at(2)));
    learningSubjects.insert(std::make_pair(3, university.subjects.at(3)));
    currStudent = std::make_shared<StudentParticipant>("Iv Lynn", "797.506.849-74", learningSubjects);
    students.insert(std::make_pair(currStudent->getId(), currStudent));

    university.students = students;

    // now the professors
    std::unordered_map<int, std::shared_ptr<ProfessorParticipant>> professors;
    std::shared_ptr<ProfessorParticipant> currProfessor;
    std::unordered_map<int, std::shared_ptr<Subject>> teachingSubjects;

    teachingSubjects.insert(std::make_pair(2, university.subjects.at(2)));
    currProfessor = std::make_shared<ProfessorParticipant>("Jackson Vesper", "002.371.457-31", teachingSubjects);
    professors.insert(std::make_pair(currProfessor->getId(), currProfessor));
    teachingSubjects.clear();

    teachingSubjects.insert(std::make_pair(2, university.subjects.at(2)));
    teachingSubjects.insert(std::make_pair(3, university.subjects.at(3)));
    currProfessor = std::make_shared<ProfessorParticipant>("Sarah James", "559.332.637-10", teachingSubjects);
    professors.insert(std::make_pair(currProfessor->getId(), currProfessor));
    teachingSubjects.clear();

    teachingSubjects.insert(std::make_pair(3, university.subjects.at(3)));
    currProfessor = std::make_shared<ProfessorParticipant>("Lelouch VI", "921.111.916-20", teachingSubjects);
    professors.insert(std::make_pair(currProfessor->getId(), currProfessor));
    teachingSubjects.clear();

    teachingSubjects.insert(std::make_pair(1, university.subjects.at(1)));
    currProfessor = std::make_shared<ProfessorParticipant>("Àkella Lynn", "797.506.849-74", teachingSubjects);
    professors.insert(std::make_pair(currProfessor->getId(), currProfessor));

    university.professors = professors;

    // now the workshops
    std::unordered_map<int, std::shared_ptr<WorkshopEvent>> workshops;
    std::shared_ptr<WorkshopEvent> currWorkshop;

    std::unordered_map<int, std::shared_ptr<ProfessorParticipant>> professorsSubset;
    // Workshop 1: Subject 1, Professors 2 and 3
    professorsSubset.insert(std::make_pair(1, university.professors.at(1)));
    professorsSubset.insert(std::make_pair(3, university.professors.at(3)));
    currWorkshop = std::make_shared<WorkshopEvent>(
        "Literature Today",
        25,
        "2025-06-15",
        professorsSubset,
        university.subjects.at(1)
    );
    workshops.insert(std::make_pair(currWorkshop->getId(), currWorkshop));
    professorsSubset.clear();

    // Workshop 2: Subject 2, Professors 1 and 2
    professorsSubset.insert(std::make_pair(1, university.professors.at(1)));
    professorsSubset.insert(std::make_pair(2, university.professors.at(2)));
    currWorkshop = std::make_shared<WorkshopEvent>(
        "Emotional Intelligence",
        30,
        "2025-06-18",
        professorsSubset,
        university.subjects.at(2)
    );
    workshops.insert(std::make_pair(currWorkshop->getId(), currWorkshop));
    professorsSubset.clear();

    // Workshop 3: Subject 3, Professor 3 only
    professorsSubset.insert(std::make_pair(3, university.professors.at(3)));
    currWorkshop = std::make_shared<WorkshopEvent>(
        "DB Design Best Practices",
        20,
        "2025-06-20",
        professorsSubset,
        university.subjects.at(3)
    );
    workshops.insert(std::make_pair(currWorkshop->getId(), currWorkshop));
    professorsSubset.clear();

    university.workshops = workshops;

    // now the lectures
    std::unordered_map<int, std::shared_ptr<LectureEvent>> lectures;
    std::shared_ptr<LectureEvent> currLecture;

    std::unordered_map<int, std::shared_ptr<Subject>> subjectsSubset;
    std::shared_ptr<ProfessorParticipant> selectedProfessor;

    // Lecture 1: Subjects 1 & 2, Professor 2
    subjectsSubset.insert(std::make_pair(1, university.subjects.at(1)));
    subjectsSubset.insert(std::make_pair(2, university.subjects.at(2)));
    selectedProfessor = university.professors.at(2);
    currLecture = std::make_shared<LectureEvent>(
        "Interdisciplinary Thinking",
        50,
        "2025-07-01",
        subjectsSubset,
        selectedProfessor
    );
    lectures.insert(std::make_pair(currLecture->getId(), currLecture));
    subjectsSubset.clear();

    // Lecture 2: Subject 3 only, Professor 3
    subjectsSubset.insert(std::make_pair(3, university.subjects.at(3)));
    selectedProfessor = university.professors.at(3);
    currLecture = std::make_shared<LectureEvent>(
        "Advanced Database Theory",
        40,
        "2025-07-03",
        subjectsSubset,
        selectedProfessor
    );
    lectures.insert(std::make_pair(currLecture->getId(), currLecture));
    subjectsSubset.clear();

    // Lecture 3: Subjects 1, 2 & 3, Professor 4
    subjectsSubset.insert(std::make_pair(1, university.subjects.at(1)));
    subjectsSubset.insert(std::make_pair(2, university.subjects.at(2)));
    subjectsSubset.insert(std::make_pair(3, university.subjects.at(3)));
    selectedProfessor = university.professors.at(3);
    currLecture = std::make_shared<LectureEvent>(
        "Connecting Humanities & Tech",
        60,
        "2025-07-10",
        subjectsSubset,
        selectedProfessor
    );
    lectures.insert(std::make_pair(currLecture->getId(), currLecture));
    subjectsSubset.clear();

    university.lectures = lectures;

    // now the fairs
    std::unordered_map<int, std::shared_ptr<FairEvent>> fairs;
    std::shared_ptr<FairEvent> currFair;

    // Fair 1
    currFair = std::make_shared<FairEvent>(
        "Tech & Talent Showcase",
        100,
        "2025-08-01"
    );
    fairs.insert(std::make_pair(currFair->getId(), currFair));

    // Fair 2
    currFair = std::make_shared<FairEvent>(
        "Humanities Exhibition",
        80,
        "2025-08-05"
    );
    fairs.insert(std::make_pair(currFair->getId(), currFair));

    // Fair 3
    currFair = std::make_shared<FairEvent>(
        "Design Thinking Fair",
        90,
        "2025-08-10"
    );
    fairs.insert(std::make_pair(currFair->getId(), currFair));

    university.fairs = fairs;

    // now the courses
    std::unordered_map<int, std::shared_ptr<CourseEvent>> courses;
    std::shared_ptr<CourseEvent> currCourse;

    // Course 1 - Database, taught by Sarah James (teaches subjects 2 & 3)
    currCourse = std::make_shared<CourseEvent>(
        "Advanced Database Systems",
        30,
        "2025-09-01",
        university.professors.at(1), // Sarah James
        university.subjects.at(3)    // Database
    );
    courses.insert(std::make_pair(currCourse->getId(), currCourse));

    // Course 2 - Soft Skills, taught by Jackson Vesper (teaches subject 2)
    currCourse = std::make_shared<CourseEvent>(
        "Communication & Soft Skills",
        40,
        "2025-09-05",
        university.professors.at(0), // Jackson Vesper
        university.subjects.at(2)    // Soft Skills
    );
    courses.insert(std::make_pair(currCourse->getId(), currCourse));

    // Course 3 - Literature, taught by Àkella Lynn (teaches subject 1)
    currCourse = std::make_shared<CourseEvent>(
        "Contemporary Literature",
        25,
        "2025-09-10",
        university.professors.at(3), // Àkella Lynn
        university.subjects.at(1)    // Literature
    );
    courses.insert(std::make_pair(currCourse->getId(), currCourse));

    university.courses = courses;

    /* External participants // just to declare and instantiate, not going to
    actually register them in the university since it defeats the purpose
    of them being externals... */
    std::unordered_map<int, std::shared_ptr<ExternalParticipant>> externals;
    std::shared_ptr<ExternalParticipant> currExternal;

    currExternal = std::make_shared<ExternalParticipant>("Caroline Grayson", "717.665.232-50", "Stanford University");
    externals.insert({currExternal->getId(), currExternal});

    currExternal = std::make_shared<ExternalParticipant>("Diego Martinez", "471.846.680-65", "University of Buenos Aires");
    externals.insert({currExternal->getId(), currExternal});

    currExternal = std::make_shared<ExternalParticipant>("Haruki Nakamura", "106.304.291-70", "Tokyo University");
    externals.insert({currExternal->getId(), currExternal});

    // ONLINE REGISTRATIONS
    std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<StudentParticipant>>> studentOnlineRegistrations;
    std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<ProfessorParticipant>>> professorOnlineRegistrations;
    std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<ExternalParticipant>>> externalOnlineRegistrations;

    // Online student registrations
    auto sreg = std::make_shared<OnlineEventRegistration<StudentParticipant>>(
        "2025-06-01", university.students.at(1), "thomas.wayne@example.com");
    studentOnlineRegistrations.insert({sreg->getId(), sreg});

    sreg = std::make_shared<OnlineEventRegistration<StudentParticipant>>(
        "2025-06-02", university.students.at(2), "jeanne.oliver@example.com");
    studentOnlineRegistrations.insert({sreg->getId(), sreg});

    sreg = std::make_shared<OnlineEventRegistration<StudentParticipant>>(
        "2025-11-11", university.students.at(1), "thomas.wayne@example.com");
    studentOnlineRegistrations.insert({sreg->getId(), sreg});


    // Online professor registrations
    auto preg = std::make_shared<OnlineEventRegistration<ProfessorParticipant>>(
        "2025-06-03", university.professors.at(1), "jackson.vesper@example.com");
    professorOnlineRegistrations.insert({preg->getId(), preg});

    preg = std::make_shared<OnlineEventRegistration<ProfessorParticipant>>(
        "2025-06-04", university.professors.at(2), "sarah.james@example.com");
    professorOnlineRegistrations.insert({preg->getId(), preg});

    preg = std::make_shared<OnlineEventRegistration<ProfessorParticipant>>(
        "2025-01-19", university.professors.at(1), "jackson.vesper@example.com");
    professorOnlineRegistrations.insert({preg->getId(), preg});

    // Online external registrations
    auto ereg = std::make_shared<OnlineEventRegistration<ExternalParticipant>>(
        "2025-06-05", externals.at(1), "caroline.grayson@stanford.edu");
    externalOnlineRegistrations.insert({ereg->getId(), ereg});

    ereg = std::make_shared<OnlineEventRegistration<ExternalParticipant>>(
        "2025-06-06", externals.at(2), "diego.martinez@uba.ar");
    externalOnlineRegistrations.insert({ereg->getId(), ereg});

    ereg = std::make_shared<OnlineEventRegistration<ExternalParticipant>>(
        "2025-09-13", externals.at(2), "diego.martinez@uba.ar");
    externalOnlineRegistrations.insert({ereg->getId(), ereg});

    // IN-PERSON REGISTRATIONS
    std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<StudentParticipant>>> inPersonStudentRegistrations;
    std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<ProfessorParticipant>>> inPersonProfessorRegistrations;
    std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<ExternalParticipant>>> inPersonExternalRegistrations;

    // In-person student registrations
    auto ipSReg = std::make_shared<InPersonEventRegistration<StudentParticipant>>(
        "2025-06-07", university.students.at(1), true);
    inPersonStudentRegistrations.insert({ipSReg->getId(), ipSReg});

    ipSReg = std::make_shared<InPersonEventRegistration<StudentParticipant>>(
        "2025-06-08", university.students.at(2), false);
    inPersonStudentRegistrations.insert({ipSReg->getId(), ipSReg});

    ipSReg = std::make_shared<InPersonEventRegistration<StudentParticipant>>(
        "2025-01-18", university.students.at(0), false);
    inPersonStudentRegistrations.insert({ipSReg->getId(), ipSReg});

    // In-person professor registrations
    auto ipPReg = std::make_shared<InPersonEventRegistration<ProfessorParticipant>>(
        "2025-06-09", university.professors.at(1), false);
    inPersonProfessorRegistrations.insert({ipPReg->getId(), ipPReg});

    ipPReg = std::make_shared<InPersonEventRegistration<ProfessorParticipant>>(
        "2025-06-10", university.professors.at(2), true);
    inPersonProfessorRegistrations.insert({ipPReg->getId(), ipPReg});

    ipPReg = std::make_shared<InPersonEventRegistration<ProfessorParticipant>>(
        "2025-10-15", university.professors.at(3), true);
    inPersonProfessorRegistrations.insert({ipPReg->getId(), ipPReg});

    // In-person external registrations
    auto ipEReg = std::make_shared<InPersonEventRegistration<ExternalParticipant>>(
        "2025-06-11", externals.at(0), true);
    inPersonExternalRegistrations.insert({ipEReg->getId(), ipEReg});

    ipEReg = std::make_shared<InPersonEventRegistration<ExternalParticipant>>(
        "2025-06-12", externals.at(1), false);
    inPersonExternalRegistrations.insert({ipEReg->getId(), ipEReg});

    ipEReg = std::make_shared<InPersonEventRegistration<ExternalParticipant>>(
        "2025-06-13", externals.at(2), true);
    inPersonExternalRegistrations.insert({ipEReg->getId(), ipEReg});

    ipEReg = std::make_shared<InPersonEventRegistration<ExternalParticipant>>(
        "2025-03-25", externals.at(1), false);
    inPersonExternalRegistrations.insert({ipEReg->getId(), ipEReg});

    // WORKSHOPS

    // Add some external guest registrations
    workshops.at(0)->addGuestRegistration(inPersonExternalRegistrations.at(0));
    workshops.at(0)->addGuestRegistration(externalOnlineRegistrations.at(1));
    // Add some students attendees registrations
    workshops.at(0)->addAttendeeRegistration(studentOnlineRegistrations.at(2));
    workshops.at(1)->addAttendeeRegistration(inPersonStudentRegistrations.at(1));

    // LECTURES

    // Add student attendee registrations
    lectures.at(0)->addAttendeeRegistration(studentOnlineRegistrations.at(1));
    lectures.at(0)->addAttendeeRegistration(inPersonStudentRegistrations.at(1));
    lectures.at(1)->addAttendeeRegistration(inPersonStudentRegistrations.at(2));

    // FAIRS

    // Add external guests (attendees)
    // fairs.at(0)->addAttendeeRegistration(externalOnlineRegistrations.at(0)); // caroline.grayson@stanford.edu
    // fairs.at(1)->addAttendeeRegistration(inPersonExternalRegistrations.at(1)); // diego.martinez@uba.ar

    // Add presenters (could be of any participant type)
    fairs.at(0)->addPresenterRegistration(inPersonStudentRegistrations.at(0)); // university.students.at(1)
    // fairs.at(0)->addPresenterRegistration(professorOnlineRegistrations.at(1)); // sarah.james@example.com
    // fairs.at(1)->addPresenterRegistration(inPersonExternalRegistrations.at(2)); // diego.martinez@uba.ar

    // COURSES

    // Add attendee registrations
    courses.at(0)->addAttendeeRegistration(studentOnlineRegistrations.at(0)); // thomas.wayne@example.com
    courses.at(1)->addAttendeeRegistration(inPersonStudentRegistrations.at(1)); // university.students.at(2)

    // Add tutor registrations
    courses.at(0)->addTutorRegistration(studentOnlineRegistrations.at(1));
    courses.at(1)->addTutorRegistration(studentOnlineRegistrations.at(1));
    courses.at(1)->addTutorRegistration(inPersonStudentRegistrations.at(2));
}

/*
std::unordered_map<int, std::shared_ptr<ProfessorParticipant>> DataGen::generateProfessorData() {

}

std::unordered_map<int, std::shared_ptr<StudentParticipant>> DataGen::generateStudentData() {

}
std::unordered_map<int, std::shared_ptr<Subject>> DataGen::generateSubjectData() {

}

std::unordered_map<int, std::shared_ptr<WorkshopEvent>> DataGen::generateWorkshopData() {

}

std::unordered_map<int, std::shared_ptr<LectureEvent>> DataGen::generateLectureData() {

}

std::unordered_map<int, std::shared_ptr<FairEvent>> DataGen::generateFairData() {

}
std::unordered_map<int, std::shared_ptr<CourseEvent>> DataGen::generateCourseData() {

}

std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<StudentParticipant>>> DataGen::generateInPersonStudentRegistrationData() {

}

std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<ProfessorParticipant>>> DataGen::generateInPersonProfessorRegistrationData() {

}

std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<ExternalParticipant>>> DataGen::generateInPersonExternalRegistrationData() {

}

std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<StudentParticipant>>> DataGen::generateOnlineStudentRegistrationData() {

}

std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<ProfessorParticipant>>> DataGen::generateOnlineProfessorRegistrationData() {

}
std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<ExternalParticipant>>> DataGen::generateOnlineExternalRegistrationData() {

}
*/
