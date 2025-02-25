#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <string>
#include <vector>

typedef unsigned short int USHORT;

struct Record {
    std::string name;
    float weight;
    USHORT mark;
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
        std::vector<Record> getRecords();
        std::string getName();

        // Setting functions
        void addRecord(Record newRecord);
        void setRecords(std::vector<Record> newRecords);
        void changeRecord(std::string name, USHORT newMark, float newWeight);
        void changeRecord(std::string name, Record newRecord);
        void deleteRecord(std::string name);
        void changeName(std::string newName);
};

#endif