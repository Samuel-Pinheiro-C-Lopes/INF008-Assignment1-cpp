#include"course_event.h"

#include"event.h"
#include"student_participant.h"

/* Default id sequence */
int CourseEvent::currentId = 0;
int CourseEvent::nextId() {
    return CourseEvent::currentId++;
}

/* Should only receive
 * StudentParticipants */
bool CourseEvent::registerParticipant(std::shared_ptr<StudentParticipant> participant) {
    return Event::registerParticipant(participant);
}
