# ABCU Course Catalog – Red-Black Tree Implementation

**Author:** Braydon Woodward  
**Created:** December 10th, 2023  
**Updated:** March 29th, 2025

## Overview

This project implements a course catalog for ABCU's Computer Science department using a self-balancing **Red–Black Tree**. The tree stores course information (course number, title, and prerequisites) and ensures efficient insertion, search, and in-order traversal operations. By leveraging modern C++ with smart pointers (using std::shared_ptr for child nodes and std::weak_ptr for parent pointers), this implementation minimizes memory-management errors and ensures robust performance.

## Project Narrative

Traditional binary search trees (BSTs) can degrade to a linear structure in worst-case scenarios (e.g., when inserting sorted data), leading to poor performance. To overcome this, the Red–Black Tree automatically rebalances itself after insertions with a combination of rotations and recoloring. This guarantees worst-case logarithmic time complexity for insertion, search, and traversal operations.

### Key Features

- **Red–Black Tree Algorithm:**  
  The tree rebalances itself using left and right rotations along with color adjustments. This ensures a balanced tree even in worst-case insertion scenarios.

- **Smart Pointer Management:**  
  The implementation uses modern C++ memory management:
  - **Child Nodes:** Stored as std::shared_ptr<RBTreeNode>.
  - **Parent Node:** Stored as a std::weak_ptr<RBTreeNode> to prevent cyclic references.
  
- **CSV File Input:**  
  Course data is read from a CSV file with the following format:
[<CourseNumber>,<CourseTitle>[,<Prerequisite1>,<Prerequisite2>,...]
This design allows for easy updates to the course catalog without recompiling the code.

- **Performance Testing:**  
The application includes a main program with options to:
- Load and insert course records from a CSV file.
- Perform an in-order traversal to print courses.
- Search for specific courses.
- Create test records 

These options also measure the time taken for each operation, allowing you to compare performance metrics.

## Build Instructions

### Requirements

- A C++17 compatible compiler (e.g., Visual Studio 2019 or later)

### Using Visual Studio

1. **Create a Project:**
 - Open Visual Studio and create a new Console Application project.
2. **Add Files to Project:**
 - Add Course.h, Course.cpp, and main.cpp to your project.
3. **Set C++ Language Standard:**
 - Go to Project Properties → **C/C++ → Language** and set the "C++ Language Standard" to **C++17** or later.
4. **Build and Run:**
 - Build the solution and run the executable from Visual Studio.