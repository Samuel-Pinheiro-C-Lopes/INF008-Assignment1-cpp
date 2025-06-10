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
#include"cpf.h"
#include"date.h"
#include"fair_event.h"
#include"workshop_event.h"
#include"lecture_event.h"
#include"data_gen.h"

#include<iostream>
#include<string>
#include<limits>

int main (int argc, char* argv[]) {
    static const std::unordered_map<int, std::string> mainMenuOptions = {
        { 0, "Exit;" },
        { 1, "Registration Menu;" },
        { 2, "Reports Menu;" },
        { 3, "Registration to Events Menu. "}
    }; 
    static const std::unordered_map<int, std::string> reportsMenuOptions = {
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
    static const std::unordered_map<int, std::string> registrationsMenuOptions = {
        { 0, "Exit;"},
        { 1, "Register a Professor;" },
        { 2, "Register a Student;" }, 
        { 3, "Register a Subject;" },
        { 4, "Register a Workshop Event;" },
        { 5, "Register a Lecture Event;" },
        { 6, "Register a Fair Event;" },
        { 7, "Register a Course Event." }
    };
    static const std::unordered_map<int, std::string> eventRegistrationsMenuOptions = {
        { 0, "Exit;"},
        { 1, "Register Attendee to a Workshop;" },
        { 2, "Register Guest to a Workshop;" }, 
        { 3, "Register Attendee to Lecture;" },
        { 4, "Register Presenter to Fair;" },
        { 5, "Register Attendee to Fair;" },
        { 6, "Register Attendee to Course." }
    };

    std::cout << "Welcome to the events & participants manager for the university! Firstly, input a name for the universisty." << std::endl;
    University university;
    DataGen::generateDataFor(university);
    int input = -1;
    while (input != 0) {
        input = Prompt::getOptionFromInput(mainMenuOptions);

        if (!(std::cin >> input) || input > 8 || input < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter with a valid option..." << std::endl;
            input = -1;
            continue;
        }

        switch (input) {
            case (1): {
                input = Prompt::getOptionFromInput(registrationsMenuOptions);
                break;
            } case (2): {
                input = Prompt::getOptionFromInput(reportsMenuOptions);
                break;
            } case (3): {
                input = Prompt::getOptionFromInput(eventRegistrationsMenuOptions);
                break;
            }
        }

        switch(input) {
            case (1): {
                university.registerProfessor();
                break;
            } case (2): {
                university.registerStudent();
                break;
            } case (3): {
                university.registerSubject();
                break;
            } case (4): {
                university.registerWorkshop();
                break;
            } case (5): {
                university.registerLecture();
                break;
            } case (6): {
                university.registerFair();
                break;
            } case (7): {
                university.registerCourse();
                break;
            } case (8): {
                university.printSelf();
                break;
            }
        }
    }

    std::cout << "Exiting..." << std::endl;
    return 0;


    /*
    std::cout << "Hello World!" << std::endl;
    CourseEvent ce("test", 10, "20/10/2024", nullptr, nullptr);
    ce.printSelf();
    */

}
