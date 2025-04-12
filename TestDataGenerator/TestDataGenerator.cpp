/*
    File: GenerateTestData.cpp
    Author: Braydon Woodward (Updated)
    Created: March 28th, 2025
    Description: This program generates a test data file (ABCUCourses.txt).
                 Each record is formatted in CSV style with a course code, course title, and prerequisites.
*/

#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Open the file ABCUCourses.txt for writing (will overwrite if exists)
    std::ofstream outFile("../CSCourseTree/ABCUCourses.txt");
    if (!outFile) {
        std::cerr << "Error: Could not open ABCUCourses.txt for writing." << std::endl;
        return 1;
    }

    // Generate 775 test records, from TEST1000 to TEST2999
    for (int i = 1000; i < 3000; ++i) {
        std::string code = "TEST" + std::to_string(i);
        std::string record = code + ",Course Title for " + code;

        int mod = i % 4;
        if (mod == 1 || mod == 2) {
            record += ",TEST" + std::to_string(i - 1);
        }
        else if (mod == 3) {
            record += ",TEST" + std::to_string(i - 1);
            record += ",TEST" + std::to_string(i - 3);
        }
        

        outFile << record << "\n";
    }

    outFile.close();
    std::cout << "ABCUCourses.txt has been generated successfully with 2000 records." << std::endl;
    return 0;
}

