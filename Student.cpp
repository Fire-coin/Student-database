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

Student::Student(std::string fullName, USHORT grade, std::unordered_map<std::string, Subject> subjects, unsigned int id) {
    studentCount++;
    this->fullName     = fullName;
    this->ID           = id;
    this->grade        = grade;
    this->subjects     = subjects;
    this->studentClass = 'A';
}

Student::Student(std::string fullName, USHORT grade, std::unordered_map<std::string, Subject> subjects, unsigned int id, char studentClass) {
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

std::unordered_map<std::string, Subject>::iterator Student::getSubjectsStart() {
    return this->subjects.begin();
}

std::unordered_map<std::string, Subject>::iterator Student::getSubjectsEnd() {
    return this->subjects.end();
}


Subject& Student::getSubject(std::string subjectName) {
    static Subject defaultSubject;
    if (this->subjects.find(subjectName) != this->subjects.end()) 
        return this->subjects[subjectName];
    else
        return defaultSubject;
}


char Student::getClass() {
    return this->studentClass;
}

void Student::addSubject(std::string subjectName, Subject newSubject) {
    this->subjects[subjectName] = newSubject;
}

void Student::setSubjects(std::unordered_map<std::string, Subject> newSubjects) {
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