#include "Student.hpp"
#include <iostream>

Student::Student() {
    studentCount++;
    this->fullName     = new char[1];
    this->ID           = studentCount;
    this->grade        = -1;
    this->subjects     = {};
    this->studentClass = 'A';
}

Student::Student(const char* fullName, USHORT grade) {
    studentCount++;
    this->fullName     = new char[strlen(fullName) + 1];
    strcpy(this->fullName, fullName);
    this->ID           = studentCount;
    this->grade        = grade;
    this->subjects     = {};
    this->studentClass = 'A';
}

Student::Student(const char* fullName, USHORT grade, unsigned int id) {
    studentCount++;
    this->fullName     = new char[strlen(fullName) + 1];
    strcpy(this->fullName, fullName);
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = {};
    this->studentClass = 'A';
}

Student::Student(const char* fullName, USHORT grade, unsigned int id, char studentClass) {
    studentCount++;
    this->fullName     = new char[strlen(fullName) + 1];
    strcpy(this->fullName, fullName);
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = {};
    this->studentClass = studentClass;
}

Student::Student(const char* fullName, USHORT grade, std::vector<Subject> subjects, unsigned int id) {
    studentCount++;
    this->fullName     = new char[strlen(fullName) + 1];
    strcpy(this->fullName, fullName);
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = subjects;
    this->studentClass = 'A';
}

Student::Student(const char* fullName, USHORT grade, std::vector<Subject> subjects, unsigned int id, char studentClass) {
    studentCount++;
    this->fullName     = new char[strlen(fullName) + 1];
    strcpy(this->fullName, fullName);
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = subjects;
    this->studentClass = studentClass;
}


char* Student::getName() {
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

char Student::getClass() {
    return this->studentClass;
}

void Student::addSubject(Subject newSubject) {
    this->subjects.push_back(newSubject);
}

void Student::setSubjects(std::vector<Subject> newSubjects) {
    this->subjects = newSubjects;
}

void Student::setName(const char* newName) {
    delete[] this->fullName;
    this->fullName = new char[strlen(newName) + 1];
    strcpy(this->fullName, newName);
}

void Student::setGrade(USHORT newGrade) {
    this->grade = newGrade;
}

void Student::setID(unsigned int newID) {
    this->ID = newID;
}

void Student::setClass(char newClass) {
    this->studentClass = newClass;
}

Student::~Student() {
    delete[] this->fullName;
    for (Subject& s : this->subjects) {
        s.~Subject();
    }
    this->subjects.clear();
}

int Student::studentCount = 0;