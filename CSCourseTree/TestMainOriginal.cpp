/*
    File: TestMain.cpp
    Author: Braydon Woodward (Updated)
    Created: March 28th, 2025
    Description: Test program for comparing performance of operations
                 (loading, inserting, searching, traversal) in the binary course catalog tree.
*/

#include "Course.h"
#include <iostream>
#include <chrono>
#include <filesystem>
#include <string>
#include <limits>

// Function: testLoadingPerformance
// Description: Loads the course catalog from a CSV file and measures the time taken.
static void testLoadingPerformance(CourseTree* tree, const std::string& fileName) {
    std::cout << "\n[TEST] Loading Performance...\n";
    auto start = std::chrono::high_resolution_clock::now();
    tree->loadDataStructure(fileName);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Loading + insertion time: " << duration.count() << " seconds\n";
}

// Function: testTraversalPerformance
// Description: Performs an in-order traversal of the tree and measures the time taken.
static void testTraversalPerformance(CourseTree* tree) {
    std::cout << "\n[TEST] In-Order Traversal Performance...\n";
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Traversal time: " << duration.count() << " seconds\n";
}

// Function: testSearchPerformance
// Description: Searches for multiple courses and measures the time taken.
static void testSearchPerformance(CourseTree* tree, const std::vector<std::string>& courseNumbers) {
    std::cout << "\n[TEST] Search Performance...\n";
    
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& number : courseNumbers) {
        Course result = tree->search(number);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Total search time for " << courseNumbers.size()
        << " searches: " << duration.count() << " seconds\n";
}

int main(int argc, char* argv[]) {
    // Print current working directory for debugging.
    std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <CSV file name>\n";
        return 1;
    }
    std::string fileName(argv[1]);


    CourseTree* courseTree = new CourseTree();

    int choice = 0;
    while (choice != 4) {
        std::cout << "\n--- Performance Testing Menu ---\n";
        std::cout << "1. Test Load + Insertion Performance\n";
        std::cout << "2. Test In-Order Traversal Performance\n";
        std::cout << "3. Test Search Performance\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: { // Test loading/insertion performance
            testLoadingPerformance(courseTree, fileName);
            break;
        }
        case 2: // Test in-order traversal performance 
            testTraversalPerformance(courseTree);
            break;
        case 3: { // Test search performance
            std::vector<std::string> testCourses = {
                "CSCI100", "CSCI150", "MATH200", "MATH249",
                "PHYS300", "PHYS349", "CHEM400", "CHEM429",
                "BIO500",  "BIO529",  "ENGL600", "ENGL619",
                "HIST700", "HIST719"
            };
            testSearchPerformance(courseTree, testCourses);
            break;
        }
        case 4:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    // Clean up
    delete courseTree;
    return 0;
}
