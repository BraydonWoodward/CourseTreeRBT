/*
    File: main.cpp
    Author: Braydon Woodward (Updated)
    Created: [Current Date]
    Description: Performance test program for the Red–Black Tree implementation of the course catalog.
                 Measures loading/insertion, in‑order traversal, and search performance.
*/

#include "Course.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <limits>
#include <filesystem>

void testLoadingPerformance(RedBlackTree& tree, const std::string& fileName) {
    std::cout << "\n[TEST] Loading Performance...\n";
    auto start = std::chrono::high_resolution_clock::now();
    tree.loadDataStructure(fileName);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Loading + insertion time: " << duration.count() << " seconds\n";
}

void testTraversalPerformance(const RedBlackTree& tree) {
    std::cout << "\n[TEST] In-Order Traversal Performance...\n";
    auto start = std::chrono::high_resolution_clock::now();
    tree.inOrder();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Traversal time: " << duration.count() << " seconds\n";
}

void testSearchPerformance(const RedBlackTree& tree, const std::vector<std::string>& courseNumbers) {
    std::cout << "\n[TEST] Search Performance...\n";
    auto start = std::chrono::high_resolution_clock::now();
    for (const auto& code : courseNumbers) {
        auto result = tree.search(code);
        // For performance testing, we do not print each result.
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Total search time for " << courseNumbers.size()
        << " searches: " << duration.count() << " seconds\n";
}

int main(int argc, char* argv[]) {
    std::cout << "Current working directory: " << std::filesystem::current_path() << "\n";
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <CSV file name>\n";
        return 1;
    }
    std::string fileName(argv[1]);

    RedBlackTree tree;

    int choice = 0;
    while (choice != 4) {
        std::cout << "\n--- Red-Black Tree Performance Testing Menu ---\n";
        std::cout << "1. Test Load + Insertion Performance\n";
        std::cout << "2. Test In-Order Traversal Performance\n";
        std::cout << "3. Test Search Performance\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            testLoadingPerformance(tree, fileName);
            break;
        case 2:
            testTraversalPerformance(tree);
            break;
        case 3: {
            std::vector<std::string> searchCourses = {
                "CSCI100", "CSCI150", "MATH200", "MATH249",
                "PHYS300", "PHYS349", "CHEM400", "CHEM429",
                "BIO500",  "BIO529",  "ENGL600", "ENGL619",
                "HIST700", "HIST719"
            };
            testSearchPerformance(tree, searchCourses);
            break;
        }
        case 4:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
