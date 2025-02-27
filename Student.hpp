#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include "Subject.hpp"

typedef unsigned short int USHORT;

class Student {
    private:
        unsigned int ID;
        char* fullName;
        USHORT grade;
        std::vector<Subject> subjects;
        char studentClass;
    public:
        static int studentCount;
        // Constructors
        Student();
        Student(const char* fullName, USHORT grade);
        Student(const char* fullName, USHORT grade, unsigned int id);
        Student(const char* fullName, USHORT grade, unsigned int id, char studentClass);
        Student(const char* fullName, USHORT grade, std::vector<Subject> subjects, unsigned int id);
        Student(const char* fullName, USHORT grade, std::vector<Subject> subjects, unsigned int id, char studentClass);
        ~Student();

        // Accesing functions
        char* getName();
        USHORT getGrade();
        unsigned int getID();
        std::vector<Subject> getSubjects();
        char getClass();
        
        // Setting functions
        void addSubject(Subject newSubject);
        void setSubjects(std::vector<Subject> newSubjects);
        void setName(const char* newName);
        void setGrade(USHORT newGrade);
        void setID(unsigned int newID);
        void setClass(char newClass);
};

#endif