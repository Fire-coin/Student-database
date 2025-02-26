#include "Student.hpp"
#include <iostream>

Student::Student() {
    studentCount++;
    this->fullName  = "";
    this->ID        = studentCount;
    this->grade     = -1;
    this->subjects  = {};
}

Student::Student(std::string fullName, USHORT grade) {
    studentCount++;
    this->fullName = fullName;
    this->ID       = studentCount;
    this->grade    = grade;
    this->subjects = {};
}

Student::Student(std::string fullName, USHORT grade, unsigned int id) {
    studentCount++;
    this->fullName = fullName;
    this->ID       = id;
    this->grade    = grade;
    this->subjects = {};
}

Student::Student(std::string fullName, USHORT grade, std::vector<Subject> subjects, unsigned int id) {
    studentCount++;
    this->fullName = fullName;
    this->ID       = id;
    this->grade    = grade;
    this->subjects = subjects;
}

std::string Student::getName() {
    return this->fullName;
}

USHORT Student::getGrade() {
    return this->grade;
}

unsigned int Student::getID() {
    return this->ID;
}

std::vector<Subject> Student::getSubjects() {
    return this->subjects;
}

void Student::addSubject(Subject newSubject) {
    this->subjects.push_back(newSubject);
}

void Student::setSubjects(std::vector<Subject> newSubjects) {
    this->subjects = newSubjects;
}

void Student::setName(std::string newName) {
    this->fullName = newName;
}

void Student::setGrade(USHORT newGrade) {
    this->grade = newGrade;
}

void Student::setID(unsigned int newID) {
    this->ID = newID;
}

int Student::studentCount = 0;