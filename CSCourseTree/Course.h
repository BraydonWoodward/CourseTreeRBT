/*
    File: Course.h
    Author: Braydon Woodward
    Created: December 10th, 2023 [Updated March 29th, 2025]
    Structure: Course
    Description: Course.cpp header file
*/
#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <optional>
#include <filesystem>

/*
* Structure: Course
* Description: Holds course details including its number, title, and prerequisites.
*/

struct Course {
    std::string courseNumber;  // unique identifier
    std::string courseTitle;
    std::vector<std::string> prerequisites;

    // Default constructor
    Course() : courseNumber(""), courseTitle("") {}

    Course(const std::string& number, const std::string& title)
        : courseNumber(number), courseTitle(title) {
    }

    // Prints prerequisites.
    void printPrerequisites() const {
        for (const auto& prereq : prerequisites)
            std::cout << prereq << " ";
        std::cout << std::endl;
    }

    // Adds a prerequisite.
    void addPrerequisite(const std::string& prereq) {
        prerequisites.push_back(prereq);
    }
};

// Enumeration for node colors in the Red-Black Tree.
enum Color { RED, BLACK };

/*
* Structure: RBTreeNode
* Description: Represents a node in the Red-Black Tree using smart pointers.
*              Uses std::shared_ptr for child nodes and std::weak_ptr for the parent.
*/
struct RBTreeNode {
    Course course;                            
    Color color;                             
    std::shared_ptr<RBTreeNode> left;         
    std::shared_ptr<RBTreeNode> right;        
    std::weak_ptr<RBTreeNode> parent;         

    // Constructor initializes node with the given course; default color is RED.
    RBTreeNode(const Course& c)
        : course(c), color(RED), left(nullptr), right(nullptr), parent() {
    }
};

/*
*
* Class: RedBlackTree
* Description: Implements a Red-Black Tree for storing Course objects,
*              supporting insertion, in-order traversal, searching, and
*              loading data from a CSV file.
*/
class RedBlackTree {
private:
    std::shared_ptr<RBTreeNode> root;  // Root of the tree

    // Helper: In‑order traversal that prints node data.
    void inOrderHelper(const std::shared_ptr<RBTreeNode>& node) const;

    // Performs left rotation around node x.
    void leftRotate(std::shared_ptr<RBTreeNode> x);

    // Performs right rotation around node x.
    void rightRotate(std::shared_ptr<RBTreeNode> x);

    // Restores Red–Black properties after insertion.
    void insertFixup(std::shared_ptr<RBTreeNode> z);

    // Recursive helper for searching.
    std::shared_ptr<RBTreeNode> searchHelper(const std::shared_ptr<RBTreeNode>& node, const std::string& courseNumber) const;

public:
    RedBlackTree();
    ~RedBlackTree() = default; // smart pointers handle cleanup

    // Inserts a course into the tree.
    void insert(const Course& course);

    // Searches for a course by course number. Returns an optional Course.
    std::optional<Course> search(const std::string& courseNumber) const;

    // Performs an in‑order traversal of the tree.
    void inOrder() const;

    // Loads course data from a CSV file.
    void loadDataStructure(const std::string& fileName);
};


#endif


