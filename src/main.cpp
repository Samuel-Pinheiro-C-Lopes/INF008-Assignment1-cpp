#include<iostream>
#include<string>

#include"entity.h"
#include"event.h"
#include"participant.h"
#include"course_event.h"
#include"student_participant.h"
#include"professor_participant.h"
#include"university.h"
#include"registration.h"
#include"in_person_event_registration.h"
#include"online_event_registration.h"

/* last ideas:
 * Changes: Identificable -> Entity and the registrations in Event.h -> guestRegistrations
 * Entity -> NamedEntity (those changes make the names more congruent)
 * More explicit documentation for the registration approach...

int main (int argc, char* argv[]) {
    std::cout << "Hello World!" << std::endl;
    CourseEvent ce("test", 10, "20/10/2024", nullptr, nullptr);
    ce.printSelf();

}
