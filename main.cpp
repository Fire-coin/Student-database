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
#include <utility>
#include <cstring>
#include <cmath>

// make permisions possible
enum class Permition {
    admin,
    teacher,
    student
};
// constexpr char USERNAMES[14] = "usernames.txt";
// constexpr char DATA[] = "data.txt";
// constexpr std::pair<int, int> gradeSpan = {1, 13};
// typedef unsigned short int USHORT;

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
int convertDate(const char* date); // Convert normal date into program native one
// std::string convertDate(int date);
int loadDataFromFile(const std::string& filename);

Subject* getSubjects(const char* studentName, int grade, const char* subjectName);
int editRecord(const char* studentName, int grade, const char* subjectName, const char* recordName, const char* newName, int newMark, float newWeight, int newDate);
int removeRecord(const char* studentName, int grade, const char* subjectName, const char* recordName);
int addRecord(const char* studentName, int grade, const char* subjectName, const char* recordName, int mark, float weight, int date);

int getSubjectData(const char* subjectName, int grade, const char* filename);
int getClassData(const char className, int grade, const char* filename);
int getStudentData(const char className, int grade, const char* studentName, const char* filename);

int main() {

    // int success = loadDataFromFile(DATA);
    // if (success == 0) {
    //     std::cout << "Data loaded successfully\n";
    // }

    // for (auto i : subjectsMap) {
    //     std::cout << i.first << '\n';
    //     for (auto j : i.second) {
    //         std::cout << j.first << '\n';
    //         for (auto k : j.second) {
    //             std::cout << k->getName() << ' ' << k->getID() << ' ' << k->getClass() << '\n';
    //             for (auto h : k->getSubject(j.first).getRecords()) {
    //                 std::cout << h.name << ' ' << h.mark << '\n';
    //             }
    //         }
    //     }
    // }
    // success = getSubjectData("Meth", 10, "subjectData.txt");
    // if (success == 0) {
    //     std::cout << "Subject data written successfully\n";
    // }

    // success = getClassData('B', 10, "classData.txt");
    // if (success == 0) {
    //     std::cout << "Class data written successfully\n";
    // }
    // editRecord("Sophia Martinez", 10, "Math", "Final Exam", "Final Exam", 34, 3.0f, 950);

    // success = getStudentData('C', 10, "Sophia Martinez", "SophiaData.txt");
    // if (success == 0) {
    //     std::cout << "Student data written successfully\n";
    // }

    return 0;
}

// <<Tranfering function>>
int getStudentData(const char className, int grade, const char* studentName, const char* filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        auto student = std::find_if(classesMap[grade][className].begin(), classesMap[grade][className].end(), [studentName](std::shared_ptr<Student> stud) {
            return std::strcmp(stud->getName().c_str(), studentName) == 0;
        });
        outFile << (*student)->getName() << ',' << (*student)->getID();
        for (auto subject = (*student)->getSubjectsStart(); subject != (*student)->getSubjectsEnd(); ++subject) {
            int totalMark = 0;
            float totalWeight = 0.0f;
            outFile << ',' << subject->first;
            for (const Record& record : subject->second.getRecords()) {
                outFile << '$' << record.name << '|' << record.mark << '|' << record.weight << '|' << record.date;
                totalMark += (record.mark * record.weight);
                totalWeight += record.weight;
            }
            outFile << '@' << std::round(totalMark / totalWeight) << '@' << totalMark << ',' << totalWeight << '$';
        }
        outFile << '\n';
    } else {
        return -1; // Could not open file
    }

    outFile.close();
    return 0;
}

// <<Tranfering function>>
int getClassData(const char className, int grade, const char* filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (auto student = classesMap[grade][className].begin(); student != classesMap[grade][className].end(); ++student) {
            outFile << (*student)->getName() << ',' << (*student)->getID();
            for (auto subject = (*student)->getSubjectsStart(); subject != (*student)->getSubjectsEnd(); ++subject) {
                int totalMark = 0;
                float totalWeight = 0.0f;
                outFile << ',' << subject->first;
                for (const Record& record : subject->second.getRecords()) {
                    outFile << '$' << record.name << '|' << record.mark << '|' << record.weight << '|' << record.date;
                    totalMark += (record.mark * record.weight);
                    totalWeight += record.weight;
                }
                outFile << '@' << std::round(totalMark / totalWeight) << '@' << '$';
            }
            outFile << '\n';
        }
    } else {
        return -1; // Could not open file
    }
    outFile.close();
    return 0;
}


// <<Tranfering function>>
int getSubjectData(const char* subjectName, int grade, const char* filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (auto student = subjectsMap[grade][subjectName].begin(); student != subjectsMap[grade][subjectName].end(); ++student) {
            Subject& subject = (*student)->getSubject(subjectName);
            int totalMark = 0;
            float totalWeight = 0.0f;
            outFile << (*student)->getName() << ',' << (*student)->getID() << ',';
            for (const Record& record : subject.getRecords()) {
                outFile << '$' << record.name << '|' << record.mark << '|' << record.weight << '|' << record.date;
                totalMark += (record.mark * record.weight);
                totalWeight += record.weight;
            }
            outFile << '@' << std::round(totalMark / totalWeight) << '@' << "$\n";
        }
    } else {
        return -1; // Could not open file
    }
    outFile.close();

    return 0;
}

// extern "C" {
    
//     // void EMSCRIPTEN_KEEPALIVE getDataOfSubject(const )
// }

// <<Tranfering function>>
Subject* getSubjects(const char* studentName, int grade, const char* subjectName) {
    auto it = std::find_if(subjectsMap[grade][subjectName].begin(),
    subjectsMap[grade][subjectName].end(), [studentName](std::shared_ptr<Student> student) {
        return std::strcmp(student->getName().c_str(), studentName) == 0;
    });
    
    if (it == subjectsMap[grade][subjectName].end()) {
        return nullptr; // Student does not study this subject
    }
    
    return &(*it)->getSubject(subjectName);
}

// <<Tranfering function>>
int addRecord(const char* studentName, int grade, const char* subjectName, const char* recordName, int mark, float weight, int date) {
    Subject* sub = getSubjects(studentName, grade, subjectName);
    if (sub) {
        sub->addRecord(recordName, mark, weight, date);
        return 0;
    }
    return -1;
}

// <<Tranfering function>>
int removeRecord(const char* studentName, int grade, const char* subjectName, const char* recordName) {
    Subject* sub = getSubjects(studentName, grade, subjectName);
    if (sub) {
        sub->deleteRecord(recordName);
        return 0;
    }
    return -1;
}

// <<Tranfering function>>
// Lets you edit record of a user
int editRecord(const char* studentName, int grade, const char* subjectName, const char* recordName, const char* newName, int newMark, float newWeight, int newDate) {
    Subject* sub = getSubjects(studentName, grade, subjectName);
    if (sub) {
        sub->changeRecord(recordName, newName, newMark, newWeight, newDate); // Editing record
        return 0;
    }
    return -1;
}

// <<Tranfering function>>
// Loads student data from specified file. Stores it into
// global maps: classesMap & subjectsMap.
int loadDataFromFile(const std::string& filename) {
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
            for (int i = 4; i < arguments.size(); ++i) {
                records = split(arguments[i], '$');
                Subject subject = Subject();
                for (int j = 1; j < records.size(); ++j) {
                    details = split(records[j], '|');
                    subject.addRecord(details[0], std::stoi(details[1]), std::stof(details[2]), std::stoi(details[3]));
                }
                student->addSubject(records[0], subject); // Adding subject to student
            }
            // Adding student into one's class
            classesMap[student->getGrade()][student->getClass()].push_back(student);
            for (auto sub = student->getSubjectsStart(); sub != student->getSubjectsEnd(); ++sub) {
                // std::cout << "here\n";
                subjectsMap[student->getGrade()][sub->first].push_back(student);
            }
        }
    } else {
        std::cerr << "Could not open file " << filename << '\n';
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

// <<Tranfering function>>
// Converts date from format DD/MM/YYYY into
// amount of days passed since Jan 1 2000.
int convertDate(const char* dateStr) {
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