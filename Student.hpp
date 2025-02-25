#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include "Subject.hpp"

typedef unsigned short int USHORT;

class Student {
    private:
        unsigned int ID;
        std::string fullName;
        USHORT grade;
        std::vector<Subject> subjects;
    public:
        static int studentCount;
        // Constructors
        Student();
        Student(std::string fullName, USHORT grade);
        Student(std::string fullName, USHORT grade, unsigned int id);
        Student(std::string fullName, USHORT grade, std::vector<Subject> subjects, unsigned int id);

        // Accesing functions
        std::string getName();
        USHORT getGrade();
        unsigned int getID();
        std::vector<Subject> getSubjects();
        
        // Setting functions
        void addSubject(Subject newSubject);
        void setSubjects(std::vector<Subject> newSubjects);
        void setName(std::string newName);
        void setGrade(USHORT newGrade);
        void setID(unsigned int newID);
};

#endif