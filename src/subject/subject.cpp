#include"subject.h"

#include<iostream>
#include<unordered_map>
#include<memory>
#include<limits>

/* Default id sequence */
int Subject::currentId = 0;
int Subject::nextId() {
    return Subject::currentId++;
}
