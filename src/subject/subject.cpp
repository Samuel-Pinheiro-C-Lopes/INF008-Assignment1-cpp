#include"subject.h"

/* Default id sequence */
int Subject::currentId = 0;
int Subject::nextId() {
    return Subject::currentId++;
}
