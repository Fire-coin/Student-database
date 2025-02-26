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
constexpr int dateStart =  946684800;

std::vector<std::string> split(const std::string& line, const char& delimiter);
int convertDate(const std::string& date);
std::string convertDate(int date);

int main() {
    std::ifstream fin(DATA);
    if (fin.is_open()) {
        std::vector<std::string> arr;
        std::string line;
        while (std::getline(fin, line, ';')) {
            arr = split(line, ',');
            for (auto i: arr) {
                std::cout << i << '\n';
            }
            // std::cout << '\n';
        }
    } else {
        std::cerr << "Could not open file " << DATA << '\n';
    }
    std::cout << convertDate("20/02/2025");


    return 0;
}

std::vector<std::string> split(const std::string& line, const char& delimiter) {
    std::vector<std::string> output;
    std::stringstream ss(line);
    std::string helpingLine;
    while (std::getline(ss, helpingLine, delimiter)) {
        output.push_back(helpingLine);
    }

    return output;
}

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