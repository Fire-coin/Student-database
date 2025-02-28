#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <string>
#include <vector>

typedef unsigned short int USHORT;

// Date will be counted in days from 01/jan/2000

struct Record {
    std::string name;
    float weight;
    USHORT mark;
    int date;
};

class Subject {
    private:
        std::string subjectName;
        std::vector<Record> records;
    public:
        Subject();
        Subject(std::string name);
        Subject(std::string name, std::vector<Record> records);

        // Getting function
        const std::vector<Record>& getRecords();
        std::string getName();

        // Setting functions
        void addRecord(Record newRecord);
        void addRecord(std::string name, USHORT mark, float weight, int date);
        void setRecords(std::vector<Record> newRecords);
        void changeRecord(std::string name, std::string newName, USHORT newMark, float newWeight, int newDate);
        void changeRecord(std::string name, Record newRecord);
        void deleteRecord(std::string name);
        void changeName(std::string newName);
};

#endif