#include<iostream>
#include<string>

#include"entity.h"
#include"event.h"
#include"participant.h"
#include"course_event.h"
#include"student_participant.h"
#include"professor_participant.h"

int main (int argc, char* argv[]) {
    std::cout << "Hello World!" << std::endl;
    CourseEvent ce("test", 10, "20/10/2024");
    ce.printSelf();

}
