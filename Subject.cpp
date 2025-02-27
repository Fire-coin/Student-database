#include "Subject.hpp"
#include <iostream>
#include <algorithm>
#include <cstring>


void sortTests(std::vector<Record>& records) {
    std::sort(records.begin(), records.end(), [](auto& record1, auto& record2) {
        return record1.date < record2.date;
    });
}

Subject::Subject() {
    this->subjectName = "None";
    this->records = {};
}

Subject::Subject(const char* name) {
    this->subjectName = new char[strlen(name) + 1];
    strcpy(this->subjectName, name);
    this->records = {};
}

Subject::Subject(const char* name, std::vector<Record> records) {
    this->subjectName = new char[strlen(name) + 1];
    strcpy(this->subjectName, name);
    this->records = records;
}

std::vector<Record> Subject::getRecords() {
    return this->records;
}

char* Subject::getName() {
    return this->subjectName;
}

void Subject::addRecord(Record newRecord) {
    this->records.push_back(newRecord);
    sortTests(this->records);
}

void Subject::addRecord(const char* name, USHORT mark, float weight, int date) {
    Record r;
    r.name = new char[strlen(name) + 1];
    strcpy(r.name, name);
    r.mark = mark;
    r.weight = weight;
    r.date = date;
    this->records.push_back(r);
}

void Subject::setRecords(std::vector<Record> newRecords) {
    this->records = newRecords;
}

void Subject::changeRecord(const char* name, const char* newName, USHORT newMark, float newWeight, int newDate) {
    auto it = std::find_if(this->records.begin(), this->records.end(), [this, name](auto& record) {
        return record.name == name;
    });
    if (it == this->records.end()) {
        throw std::runtime_error("No record with name: " + *name);
    } else {
        if (strcmp(name, newName) != 0) {
            delete[] it->name;
            it->name = new char[strlen(newName) + 1];
            strcpy(it->name, newName);
        }
        it->mark = newMark;
        it->weight = newWeight;
        it->date = newDate;
    }
    sortTests(this->records);
}

void Subject::changeRecord(const char* name, Record newRecord) {
    auto it = std::find_if(this->records.begin(), this->records.end(), [this, name](auto& record) {
        return record.name == name;
    });
    if (it == this->records.end()) {
        throw std::runtime_error("No record with name: " + *name);
    } else {
        delete[] it->name;
        *it = newRecord;
    }
    sortTests(this->records);
}

void Subject::deleteRecord(const char* name) {
    auto it = std::find_if(this->records.begin(), this->records.end(), [this, name](auto& record) {
        return record.name == name;
    });
    if (it == this->records.end()) {
        throw std::runtime_error("No record with name: " + *name);
    } else {
        delete[] it->name;
        records.erase(it);
    }
}

void Subject::changeName(const char* newName) {
    delete[] this->subjectName;
    this->subjectName = new char[strlen(newName + 1)];
    strcpy(this->subjectName, newName);
}

Subject::~Subject() {
    delete[] this->subjectName;

    for (Record& r : this->records) {
        delete[] r.name;
    }
    this->records.clear();
}