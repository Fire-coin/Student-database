#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <vector>
#include "Subject.hpp"
#include <unordered_map>

typedef unsigned short int USHORT;

class Student {
    private:
        unsigned int ID;
        std::string fullName;
        USHORT grade;
        std::unordered_map<std::string, Subject> subjects;
        char studentClass;
    public:
        static int studentCount;
        // Constructors
        Student();
        Student(std::string fullName, USHORT grade);
        Student(std::string fullName, USHORT grade, unsigned int id);
        Student(std::string fullName, USHORT grade, unsigned int id, char studentClass);
        Student(std::string fullName, USHORT grade, std::unordered_map<std::string, Subject> subjects, unsigned int id);
        Student(std::string fullName, USHORT grade, std::unordered_map<std::string, Subject> subjects, unsigned int id, char studentClass);

        // Accesing functions
        std::string getName();
        USHORT getGrade();
        unsigned int getID();
        std::unordered_map<std::string, Subject>::iterator getSubjectsStart();
        std::unordered_map<std::string, Subject>::iterator getSubjectsEnd();
        Subject& getSubject(std::string subjectName);
        char getClass();
        
        // Setting functions
        void addSubject(std::string subjectName, Subject newSubject);
        void setSubjects(std::unordered_map<std::string, Subject> newSubjects);
        void setName(std::string newName);
        void setGrade(USHORT newGrade);
        void setID(unsigned int newID);
        void setClass(char newClass);
};

#endif