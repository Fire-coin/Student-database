#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>

typedef unsigned short int USHORT;

// Date will be counted in days from 01/jan/2000

struct Record {
    char* name;
    float weight;
    USHORT mark;
    int date;
};

class Subject {
    private:
        char* subjectName;
        std::vector<Record> records;
    public:
        Subject();
        Subject(const char* name);
        Subject(const char* name, std::vector<Record> records);
        ~Subject();

        // Getting function
        std::vector<Record> getRecords();
        char* getName();

        // Setting functions
        void addRecord(Record newRecord);
        void addRecord(const char* name, USHORT mark, float weight, int date);
        void setRecords(std::vector<Record> newRecords);
        void changeRecord(const char* name, const char* newName, USHORT newMark, float newWeight, int newDate);
        void changeRecord(const char* name, Record newRecord);
        void deleteRecord(const char* name);
        void changeName(const char* newName);
};

#endif