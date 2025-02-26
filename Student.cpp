#include "Student.hpp"
#include <iostream>

Student::Student() {
    studentCount++;
    this->fullName     = "";
    this->ID           = studentCount;
    this->grade        = -1;
    this->subjects     = {};
    this->studentClass = 'A';
}

Student::Student(std::string fullName, USHORT grade) {
    studentCount++;
    this->fullName     = fullName;
    this->ID           = studentCount;
    this->grade        = grade;
    this->subjects     = {};
    this->studentClass = 'A';
}

Student::Student(std::string fullName, USHORT grade, unsigned int id) {
    studentCount++;
    this->fullName     = fullName;
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = {};
    this->studentClass = 'A';
}

Student::Student(std::string fullName, USHORT grade, unsigned int id, char studentClass) {
    studentCount++;
    this->fullName     = fullName;
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = {};
    this->studentClass = studentClass;
}

Student::Student(std::string fullName, USHORT grade, std::vector<Subject> subjects, unsigned int id) {
    studentCount++;
    this->fullName     = fullName;
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = subjects;
    this->studentClass = 'A';
}

Student::Student(std::string fullName, USHORT grade, std::vector<Subject> subjects, unsigned int id, char studentClass) {
    studentCount++;
    this->fullName     = fullName;
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = subjects;
    this->studentClass = studentClass;
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

char Student::getClass() {
    return this->studentClass;
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

void Student::setClass(char newClass) {
    this->studentClass = newClass;
}

int Student::studentCount = 0;