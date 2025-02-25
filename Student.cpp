#include "Student.hpp"
#include <iostream>

Student::Student(std::string fullName, USHORT grade) {
    this->fullName = fullName;
    this->grade = grade;
}

Student::Student(unsigned int id, std::string fullName, USHORT grade) {
    this->ID = id;
    this->fullName = fullName;
    this->grade = grade;
}

Student::Student(unsigned int id, std::string fullName, USHORT grade, std::vector<Subject> subjects) {
    this->ID = id;
    this->fullName = fullName;
    this->grade = grade;
    this->subjects = subjects;
}

//TODO finish rest