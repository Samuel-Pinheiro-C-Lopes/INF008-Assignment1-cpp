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

#include <thread>
#include <chrono>

/*
 * 1 - prompt function to validate last cin (two overloads until now, yay!)
 * 2 - switchs from main to handle menu done (double yay!) (more overloads for prompt
 * cin handle function, also)
 * 3 - just cleaned the prompt a little more, adding the generic ways of dealing with
 * cin possible errors and the default print as options - added more overloads, but that's
 * fine, right? They are exactly for this, I suppose...
 * 4 - move these static menu option to the university and try to move the switchs to there?
 * I dunno... there are switchs and whiles nested so it may be complicated...
 * */

int main (int argc, char* argv[]) {
    // Presentation
    Prompt::clearScreen();
    std::cout << "┌────────────────────────────" << std::endl;
    std::cout << "│" << std::endl;
    std::cout << "│" <<  "Welcome to the events & participants manager for the university!" << std::endl;
    std::cout << "│" <<  "First, input a name for the university!" << std::endl;
    University university; // default empty constructor fetches the name.

    // If it's needed to add some test data
    if(Prompt::getFlagFromInput("Do you want to automatically generate some test data for the university?"))
        DataGen::generateDataFor(university);

    Prompt::clearScreen();
    int input = -1;
    int month = 0;
    while (input != 0) {
        Prompt::printSelectablesAsOptions(University::mainMenuOptions);

        std::cout << "│" << "Your selection: ";
        if (!Prompt::handleLastCinInput(input, University::mainMenuOptions))
            continue;

        if (input == 0)
            break;

        while (input != 0) {
            Prompt::clearScreen();
            switch (input) {
                // Registration
                case (1): {
                    Prompt::printSelectablesAsOptions(University::registrationsMenuOptions);

                    std::cout << "│" << "Your selection: ";
                    if (!Prompt::handleLastCinInput(input,
                        University::registrationsMenuOptions))
                        continue;

                    Prompt::clearScreen();
                    // Registration options
                    switch(input) {
                        case (1): {
                            if (!university.registerProfessor())
                                std::cout << "failure in registering a professor. Check the CPF." << std::endl;
                            break;
                        }
                        case (2): {
                            university.registerStudent();
                            break;
                        }
                        case (3): {
                            university.registerSubject();
                            break;
                        }
                        case (4): {
                            university.registerWorkshop();
                            break;
                        }
                        case (5): {
                            university.registerLecture();
                            break;
                        }
                        case (6): {
                            university.registerFair();
                            break;
                        }
                        case (7): {
                            university.registerCourse();
                            break;
                        }
                    }
                    if (input != 0) {
                        input = 1;
                        Prompt::getTextFromInput("Enter with any key to continue...");
                        Prompt::clearScreen();
                    }
                    break;
                } // register
                case (2): {
                    Prompt::printSelectablesAsOptions(University::reportsMenuOptions);

                    std::cout << "│" << "Your selection: ";
                    if (!Prompt::handleLastCinInput(input, University::reportsMenuOptions))
                        continue;

                    Prompt::clearScreen();
                    // Reports options
                    switch (input) {
                        case (1): {
                            university.printProfessors();
                            break;
                        }
                        case (2): {
                            university.printStudents();
                            break;
                        }
                        case (3): {
                            university.printSubjects();
                            break;
                        }
                        case (4): {
                            university.printWorkshops();
                            break;
                        }
                        case (5): {
                            university.printLectures();
                            break;
                        }
                        case (6): {
                            university.printFairs();
                            break;
                        }
                        case (7): {
                            university.printCourses();
                            break;
                        }
                        case (8): {
                            university.printSelf();
                            break;
                        }
                        case (9): {
                            std::cout << "│" << "Enter with the search month: ";
                            if (!Prompt::Prompt::handleLastCinInput(month, 1, 12))
                                continue;
                            university.printEventsByMonth(month);
                            break;
                        }
                    }
                    if (input != 0) {
                        input = 2;
                        Prompt::getTextFromInput("Enter with any key to continue...");
                        Prompt::clearScreen();
                    }
                    break;
                } // reports
                case (3): {
                    Prompt::printSelectablesAsOptions(University::eventRegistrationsMenuOptions);

                    std::cout << "│" << "Your selection: ";

                    if (!Prompt::handleLastCinInput(input, University::eventRegistrationsMenuOptions))
                        continue;

                    Prompt::clearScreen();
                    // Registrations to events options
                    switch (input) {
                        case (1): {
                            university.registerAttendeeToWorkshop();
                            break;
                        }
                        case (2): {
                            university.registerGuestToWorkshop();
                            break;
                        }
                        case (3): {
                            university.registerAttendeeToLecture();
                            break;
                        }
                        case (4): {
                            university.registerPresenterToFair();
                            break;
                        }
                        case (5): {
                            university.registerAttendeeToFair();
                            break;
                        }
                        case (6): {
                            university.registerAttendeeToCourse();
                            break;
                        }
                    }
                    if (input != 0) {
                        input = 3;
                        Prompt::getTextFromInput("Enter with any key to continue...");
                        Prompt::clearScreen();
                    }
                    break;
                } // Register to course
                case (4): {
                    std::cout << "│" << "Trying to write log file..." << std::endl;
                    if (university.generateLogFile())
                        std::cout << "│" << "Creating file named [university.json] with serialized data." << std::endl;
                    else
                        std::cout << "│" << "Failed to generate log data." << std::endl;

                    input = 0;
                    std::this_thread::sleep_for(std::chrono::seconds(3));

                    break;
                }
            } // main menu switch
        } // loop
        input = -1;
        Prompt::clearScreen();
    } // application loop
    Prompt::clearScreen();
    std::cout << "Exited" << std::endl;
    return 0;


    /*
    std::cout << "Hello World!" << std::endl;
    CourseEvent ce("test", 10, "20/10/2024", nullptr, nullptr);
    ce.printSelf();
    */

}
