#include "Subject.hpp"
#include "Student.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <ctime>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
// #include <emscripten.h>

// make permisions possible
enum class Permition {
    admin,
    teacher,
    student
};
constexpr char USERNAMES[14] = "usernames.txt";
constexpr char DATA[] = "data.txt";
constexpr std::pair<int, int> gradeSpan = {1, 13};
typedef unsigned short int USHORT;
// First key of this map is the grade of student, then there are more maps,
// and each one's key is the class of student (eg. A, B, C, .etc). The class 
// is mapped to vector of shared pointers to students. This is done to prevent 
// uneccerary iteration each time user wants to see each class individually.
std::unordered_map<int, std::unordered_map<char, std::vector<std::shared_ptr<Student>>>> classesMap;

// First key of this map is the grade of student, the grade maps to another map,
// this map has key to one's subject (eg. Math, English, .etc). The subject is
// mapped to a vector of shared pointers to students. This is done to prevent
// uneccerary iteration each time user wants to see each subject of the grade individually.
std::unordered_map<int, std::unordered_map<std::string, std::vector<std::shared_ptr<Student>>>> subjectsMap;

std::vector<std::string> split(const std::string& line, const char& delimiter);
int convertDate(const std::string& date); // Convert normal date into program native one
std::string convertDate(int date);
int loadDataFromFile(std::string filename);

int editRecord(std::string studentName, int grade, std::string subject, std::string recordName, std::string newName, USHORT newMark, float newWeight, int newDate);
int removeRecord(std::string studentName, int grade, std::string subjectName, std::string recordName);
int addRecord(std::string studentName, int grade, std::string subjectName, std::string recordName, USHORT mark, float weight, int date);
std::pair<int, std::vector<Subject>::iterator> getSubjects(std::string studentName, int grade, std::string subjectName);

int main() {

    int success = loadDataFromFile(DATA);
    if (success == 0) {
        std::cout << "Data loaded successfully\n";
    }

    return 0;
}

std::pair<int, std::vector<Subject>::iterator> getSubjects(std::string studentName, int grade, std::string subjectName) {
    
    auto it = std::find_if(subjectsMap[grade][subjectName].begin(),
        subjectsMap[grade][subjectName].end(),
        [studentName](auto student) { return student->getName() == studentName; });

    if (it == subjectsMap[grade][subjectName].end()) {
        return {-1, std::vector<Subject>::iterator()}; // Student does not study this subject
    }

    auto student = *it; // Shared pointer of student
    auto it2 = std::find_if(student->getSubjects().begin(), student->getSubjects().end(),
        [subjectName](auto sub) { return sub.getName() == subjectName; });

    if (it2 == student->getSubjects().end()) {
        return {-1, std::vector<Subject>::iterator()}; // No record of test
    }

    return {0, it2}; // Return valid iterator
}


int addRecord(std::string studentName, int grade, std::string subjectName, std::string recordName, int mark, float weight, int date) {
    auto it = std::find_if(subjectsMap[grade][subjectName].begin(), subjectsMap[grade][subjectName].end(), [studentName](auto student) {
        return student->getName() == studentName;
    });

    if (it == subjectsMap[grade][subjectName].end()) {
        return -1; // Student does not stude this subject
    }

    auto student = *it; // Shared pointer of student
    auto it2 = std::find_if(student->getSubjects().begin(), student->getSubjects().end(), [subjectName](auto sub) {
        return sub.getName() == subjectName;
    });

    if (it2 == student->getSubjects().end()) {
        return -1; // Student does not have record of writing this test on this subject
    }

    it2->addRecord(recordName, mark, weight, date);

    return 0;
}

int removeRecord(std::string studentName, int grade, std::string subjectName, std::string recordName) {
    auto it = std::find_if(subjectsMap[grade][subjectName].begin(), subjectsMap[grade][subjectName].end(), [studentName](auto student) {
        return student->getName() == studentName;
    });

    if (it == subjectsMap[grade][subjectName].end()) {
        return -1; // Student does not stude this subject
    }

    auto student = *it; // Shared pointer of student
    auto it2 = std::find_if(student->getSubjects().begin(), student->getSubjects().end(), [subjectName](auto sub) {
        return sub.getName() == subjectName;
    });

    if (it2 == student->getSubjects().end()) {
        return -1; // Student does not have record of writing this test on this subject
    }

    it2->deleteRecord(recordName);

    return 0;
}


// Lets you edit record of a user
int editRecord(std::string studentName, int grade, std::string subject, std::string recordName, std::string newName, int newMark, float newWeight, int newDate) {
    // Finding student in vector
    auto it = std::find_if(subjectsMap[grade][subject].begin(), subjectsMap[grade][subject].end(), [studentName](auto student) {
        return student->getName() == studentName;
    });

    if (it == subjectsMap[grade][subject].end()) {
        return -1; // Student does not study this subject
    }

    auto student = *it;
    auto it2 = std::find_if(student->getSubjects().begin(), student->getSubjects().end(), [subject](auto sub) {
        return sub.getName() == subject;
    });

    if (it2 == student->getSubjects().end()) {
        return -1; // Student does not have record of writing this test on this subject
    }

    it2->changeRecord(newName, newMark, newWeight, newDate); // Editing record

    return 0;
}

// Loads student data from specified file. Stores it into
// global maps: classesMap & subjectsMap.
int loadDataFromFile(std::string filename) {
    std::ifstream fin(filename);
    if (fin.is_open()) {
        // Contains all details of student like name, grade,
        // class and all subjects
        std::vector<std::string> arguments; 
        // Contains individual records from each subject
        std::vector<std::string> records;
        // Contains name, mark, wiegth and date from each record
        std::vector<std::string> details;

        // Helping buffer to load lines from file
        std::string line;

        while (std::getline(fin, line)) {
            arguments = split(line, ',');
            // Creating shared pointer to student to put in maps for faster access
            std::shared_ptr<Student> student = std::make_shared<Student>(arguments[0], std::stoi(arguments[2]), std::stoi(arguments[1]), arguments[3][0]);
            Subject subject;
            for (int i = 4; i < arguments.size(); ++i) {
                records = split(arguments[i], '$');
                subject.changeName(records[0]); // Changing name of subject
                for (int j = 1; j < records.size(); ++j) {
                    details = split(records[j], '|');
                    subject.addRecord(details[0], std::stoi(details[1]), std::stof(details[2]), std::stoi(details[3]));
                }
                student->addSubject(subject); // Adding subject to student
            }
            // Adding student into one's class
            classesMap[student->getGrade()][student->getClass()].push_back(student);
            for (auto sub : student->getSubjects()) {
                // Adding student into one's subjects
                subjectsMap[student->getGrade()][sub.getName()].push_back(student);
            }
        }
    } else {
        std::cerr << "Could not open file " << DATA << '\n';
        return -1;
    }

    return 0;
}


// Splits line on delimiter, returns vector of strings.
std::vector<std::string> split(const std::string& line, const char& delimiter) {
    std::vector<std::string> output = {};
    std::stringstream ss(line);
    std::string helpingLine;
    while (std::getline(ss, helpingLine, delimiter)) {
        output.push_back(helpingLine);
    }
    return output;
}

// Converts date from format DD/MM/YYYY into
// amount of days passed since Jan 1 2000.
int convertDate(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    
    // Parse the date string in the format DD/MM/YYYY
    ss >> std::get_time(&tm, "%d/%m/%Y");
    if (ss.fail()) {
        std::cerr << "Failed to parse date" << std::endl;
        return -1;
    }

    // Get the time for January 1, 2000
    std::tm start_tm = {};
    start_tm.tm_year = 2000 - 1900; // Year since 1900
    start_tm.tm_mon = 0;            // January
    start_tm.tm_mday = 1;           // 1st day of the month
    std::time_t start_time = std::mktime(&start_tm);

    // Convert the input date to time_t
    std::time_t input_time = std::mktime(&tm);

    // Calculate the difference in seconds
    double seconds_difference = std::difftime(input_time, start_time);

    // Convert seconds to days
    long days_difference = seconds_difference / 86400;  // 86400 seconds in a day

    return days_difference;
}