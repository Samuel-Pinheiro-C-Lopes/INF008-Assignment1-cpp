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
    Map<int, Ptr<Subject>> subjects;
    Ptr<Subject> currSubject;
    for (const String& name : {"Literature", "Soft Skills", "Database", "Web Development", "Design"}) {
        currSubject = std::make_shared<Subject>(name);
        subjects[currSubject->getId()] = currSubject;
    }
    university.subjects = subjects;

    // now the students
    Map<int, Ptr<StudentParticipant>> students;
    Ptr<StudentParticipant> currStudent;
    Map<int, Ptr<Subject>> learningSubjects;

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
    Map<int, Ptr<ProfessorParticipant>> professors;
    Ptr<ProfessorParticipant> currProfessor;
    Map<int, Ptr<Subject>> teachingSubjects;

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
    Map<int, Ptr<WorkshopEvent>> workshops;
    Ptr<WorkshopEvent> currWorkshop;

    Map<int, Ptr<ProfessorParticipant>> professorsSubset;

    // Workshop 1:
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

    // Workshop 2:
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

    // Workshop 3:
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
    Map<int, Ptr<LectureEvent>> lectures;
    Ptr<LectureEvent> currLecture;

    Map<int, Ptr<Subject>> subjectsSubset;
    Ptr<ProfessorParticipant> selectedProfessor;

    // Lecture 1:
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

    // Lecture 2:
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

    // Lecture 3:
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
    Map<int, Ptr<FairEvent>> fairs;
    Ptr<FairEvent> currFair;

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
    Map<int, Ptr<CourseEvent>> courses;
    Ptr<CourseEvent> currCourse;

    // Course 1
    currCourse = std::make_shared<CourseEvent>(
        "Advanced Database Systems",
        30,
        "2025-09-01",
        university.professors.at(1), // Sarah James
        university.subjects.at(3)    // Database
    );
    courses.insert(std::make_pair(currCourse->getId(), currCourse));

    // Course 2
    currCourse = std::make_shared<CourseEvent>(
        "Communication & Soft Skills",
        40,
        "2025-09-05",
        university.professors.at(1), // Jackson Vesper
        university.subjects.at(2)    // Soft Skills
    );
    courses.insert(std::make_pair(currCourse->getId(), currCourse));

    // Course 3
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
    Map<int, Ptr<ExternalParticipant>> externals;
    Ptr<ExternalParticipant> currExternal;

    currExternal = std::make_shared<ExternalParticipant>("Caroline Grayson", "717.665.232-50", "Stanford University");
    externals.insert({currExternal->getId(), currExternal});

    currExternal = std::make_shared<ExternalParticipant>("Diego Martinez", "471.846.680-65", "University of Buenos Aires");
    externals.insert({currExternal->getId(), currExternal});

    currExternal = std::make_shared<ExternalParticipant>("Haruki Nakamura", "106.304.291-70", "Tokyo University");
    externals.insert({currExternal->getId(), currExternal});

    // ONLINE REGISTRATIONS
    Map<int, Ptr<OnlineEventRegistration<StudentParticipant>>> studentOnlineRegistrations;
    Map<int, Ptr<OnlineEventRegistration<ProfessorParticipant>>> professorOnlineRegistrations;
    Map<int, Ptr<OnlineEventRegistration<ExternalParticipant>>> externalOnlineRegistrations;

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
    Map<int, Ptr<InPersonEventRegistration<StudentParticipant>>> inPersonStudentRegistrations;
    Map<int, Ptr<InPersonEventRegistration<ProfessorParticipant>>> inPersonProfessorRegistrations;
    Map<int, Ptr<InPersonEventRegistration<ExternalParticipant>>> inPersonExternalRegistrations;

    // In-person student registrations
    auto ipSReg = std::make_shared<InPersonEventRegistration<StudentParticipant>>(
        "2025-06-07", university.students.at(1), true);
    inPersonStudentRegistrations.insert({ipSReg->getId(), ipSReg});

    ipSReg = std::make_shared<InPersonEventRegistration<StudentParticipant>>(
        "2025-06-08", university.students.at(2), false);
    inPersonStudentRegistrations.insert({ipSReg->getId(), ipSReg});

    ipSReg = std::make_shared<InPersonEventRegistration<StudentParticipant>>(
        "2025-01-18", university.students.at(1), false);
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
        "2025-06-11", externals.at(2), true);
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
    workshops.at(1)->addGuestRegistration(inPersonExternalRegistrations.at(2));
    workshops.at(1)->addGuestRegistration(externalOnlineRegistrations.at(1));
    // Add some students attendees registrations
    workshops.at(1)->addAttendeeRegistration(studentOnlineRegistrations.at(2));
    workshops.at(2)->addAttendeeRegistration(inPersonStudentRegistrations.at(1));

    // LECTURES

    // Add student attendee registrations
    lectures.at(1)->addAttendeeRegistration(studentOnlineRegistrations.at(1));
    lectures.at(1)->addAttendeeRegistration(inPersonStudentRegistrations.at(1));
    lectures.at(2)->addAttendeeRegistration(inPersonStudentRegistrations.at(2));

    // FAIRS

    // Add external guests (attendees)
    // fairs.at(0)->addAttendeeRegistration(externalOnlineRegistrations.at(0)); // caroline.grayson@stanford.edu
    // fairs.at(1)->addAttendeeRegistration(inPersonExternalRegistrations.at(1)); // diego.martinez@uba.ar

    // Add presenters (could be of any participant type)
    fairs.at(1)->addPresenterRegistration(inPersonStudentRegistrations.at(1)); // university.students.at(1)
    // fairs.at(0)->addPresenterRegistration(professorOnlineRegistrations.at(1)); // sarah.james@example.com
    // fairs.at(1)->addPresenterRegistration(inPersonExternalRegistrations.at(2)); // diego.martinez@uba.ar

    // COURSES

    // Add attendee registrations
    courses.at(1)->addAttendeeRegistration(studentOnlineRegistrations.at(1)); // thomas.wayne@example.com
    courses.at(2)->addAttendeeRegistration(inPersonStudentRegistrations.at(2)); // university.students.at(2)

    // Add tutor registrations
    courses.at(1)->addTutorRegistration(studentOnlineRegistrations.at(2));
    courses.at(2)->addTutorRegistration(studentOnlineRegistrations.at(2));
    courses.at(2)->addTutorRegistration(inPersonStudentRegistrations.at(1));
}

/*
Map<int, Ptr<ProfessorParticipant>> DataGen::generateProfessorData() {

}

Map<int, Ptr<StudentParticipant>> DataGen::generateStudentData() {

}
Map<int, Ptr<Subject>> DataGen::generateSubjectData() {

}

Map<int, Ptr<WorkshopEvent>> DataGen::generateWorkshopData() {

}

Map<int, Ptr<LectureEvent>> DataGen::generateLectureData() {

}

Map<int, Ptr<FairEvent>> DataGen::generateFairData() {

}
Map<int, Ptr<CourseEvent>> DataGen::generateCourseData() {

}

Map<int, Ptr<InPersonEventRegistration<StudentParticipant>>> DataGen::generateInPersonStudentRegistrationData() {

}

Map<int, Ptr<InPersonEventRegistration<ProfessorParticipant>>> DataGen::generateInPersonProfessorRegistrationData() {

}

Map<int, Ptr<InPersonEventRegistration<ExternalParticipant>>> DataGen::generateInPersonExternalRegistrationData() {

}

Map<int, Ptr<OnlineEventRegistration<StudentParticipant>>> DataGen::generateOnlineStudentRegistrationData() {

}

Map<int, Ptr<OnlineEventRegistration<ProfessorParticipant>>> DataGen::generateOnlineProfessorRegistrationData() {

}
Map<int, Ptr<OnlineEventRegistration<ExternalParticipant>>> DataGen::generateOnlineExternalRegistrationData() {

}
*/
