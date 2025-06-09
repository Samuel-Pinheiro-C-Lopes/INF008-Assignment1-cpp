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
    std::cout << "Welcome to the events & participants manager for the university! Firstly, input a name for the universisty." << std::endl;
    University university;
    DataGen::generateDataFor(university);
    int input = -1;

    while (input != 0) {

        std::cout
        << "Enter with the desired option:" << std::endl
        << "[1]: Register a professor;" << std::endl
        << "[2]: Register a student;" << std::endl
        << "[3] Register a subject for the university;" << std::endl
        << "[4] Register a Workshop event;" << std::endl
        << "[5] Register a Lecture event;" << std::endl
        << "[6] Register a Fair event;" << std::endl
        << "[7] Register a Course event;" << std::endl
        << "[8] Print whole university;" << std::endl
        << "[0] Exit." << std::endl
        << "Your option: ";

        if (!(std::cin >> input) || input > 8 || input < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter with a valid option..." << std::endl;
            input = -1;
            continue;
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
