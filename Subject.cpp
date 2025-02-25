#include "Subject.hpp"
#include <iostream>
#include <algorithm>



Subject::Subject(std::string name) {
    this->subjectName = name;
    this->records = {};
}

Subject::Subject(std::string name, std::vector<Record> records) {
    this->records = records;
    this->subjectName = name;
}

std::vector<Record> Subject::getRecords() {
    return this->records;
}

std::string Subject::getName() {
    return this->subjectName;
}

void Subject::addRecord(Record newRecord) {
    this->records.push_back(newRecord);
    sortTests(this->records);
}

void Subject::setRecords(std::vector<Record> newRecords) {
    this->records = newRecords;
}

void sortTests(std::vector<Record>& records) {
    std::sort(records.begin(), records.end(), [](auto& record1, auto& record2) {
        return record1.date < record2.date;
    });
}

void Subject::changeRecord(std::string name, USHORT newMark, float newWeight, int newDate) {
    auto it = std::find_if(this->records.begin(), this->records.end(), [this, name](auto& record) {
        return record.name == name;
    });
    if (it == this->records.end()) {
        throw std::runtime_error("No record with name: " + name);
    } else {
        it->mark = newMark;
        it->weight = newWeight;
        it->date = newDate;
    }
    sortTests(this->records);
}

void Subject::changeRecord(std::string name, Record newRecord) {
    auto it = std::find_if(this->records.begin(), this->records.end(), [this, name](auto& record) {
        return record.name == name;
    });
    if (it == this->records.end()) {
        throw std::runtime_error("No record with name: " + name);
    } else {
        *it = newRecord;
    }
    sortTests(this->records);
}

void Subject::deleteRecord(std::string name) {
    auto it = std::find_if(this->records.begin(), this->records.end(), [this, name](auto& record) {
        return record.name == name;
    });
    if (it == this->records.end()) {
        throw std::runtime_error("No record with name: " + name);
    } else {
        records.erase(it);
    }
}

void Subject::changeName(std::string newName) {
    this->subjectName = newName;
}