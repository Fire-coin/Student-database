#include <iostream>
#include <stdlib.h>

int main() {
    try {
        std::system("g++ -o main.exe main.cpp Subject.cpp Student.cpp");
    } catch (const std::exception& e) {
        std::cerr << "Exception occured " << e.what() << '\n';
        return -1;
    }

    std::cout << "Succesfully builded\n";

    return 0;
}