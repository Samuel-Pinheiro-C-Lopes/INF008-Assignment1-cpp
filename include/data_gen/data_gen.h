#ifndef DATA_GEN_H
#define DATA_GEN_H

#include"professor_participant.h"
#include"student_participant.h"

#include"subject.h"

#include"workshop_event.h"
#include"lecture_event.h"
#include"fair_event.h"
#include"course_event.h"

#include"alias.h"

class University;

#include"in_person_event_registration.h"
#include"online_event_registration.h"

#include<memory>
#include<vector>
#include<unordered_map>
#include<string>

using namespace alias;

class DataGen final {
public:
    static void generateDataFor(University& u);
private:
    DataGen() = delete;
    ~DataGen() = delete;
};

#endif


/*
 s t*atic std::unordered_map<int, std::shared_ptr<ProfessorParticipant>> generateProfessorData();
 static std::unordered_map<int, std::shared_ptr<StudentParticipant>> generateStudentData();
 static std::unordered_map<int, std::shared_ptr<Subject>> generateSubjectData();
 static std::unordered_map<int, std::shared_ptr<WorkshopEvent>> generateWorkshopData();
 static std::unordered_map<int, std::shared_ptr<LectureEvent>> generateLectureData();
 static std::unordered_map<int, std::shared_ptr<FairEvent>> generateFairData();
 static std::unordered_map<int, std::shared_ptr<CourseEvent>> generateCourseData();

 static std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<StudentParticipant>>> generateInPersonStudentRegistrationData();
 static std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<ProfessorParticipant>>> generateInPersonProfessorRegistrationData();
 static std::unordered_map<int, std::shared_ptr<InPersonEventRegistration<ExternalParticipant>>> generateInPersonExternalRegistrationData();

 static std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<StudentParticipant>>> generateOnlineStudentRegistrationData();
 static std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<ProfessorParticipant>>> generateOnlineProfessorRegistrationData();
 static std::unordered_map<int, std::shared_ptr<OnlineEventRegistration<ExternalParticipant>>> generateOnlineExternalRegistrationData();
 */
