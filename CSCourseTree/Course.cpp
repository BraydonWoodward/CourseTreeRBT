/*
    File: Course.cpp
    Author: Braydon Woodward
    Created: December 10th, 2023
    Description: Binary Search tree for ABCU Computer Science course catolog 
*/

#include "Course.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

// Red-Black Tree constructor
RedBlackTree::RedBlackTree() : root(nullptr) {}

/*
*  inOrderHelper: Recursively traverses the tree in order and print course info
*/
void RedBlackTree::inOrderHelper(const std::shared_ptr<RBTreeNode>& node) const {
    if (node) {
        inOrderHelper(node->left);  // Traverse left subtree

        // Comment out to not print full course tree (testing)
        std::cout << node->course.courseNumber << ": "
            << node->course.courseTitle << " ("
            << (node->color == RED ? "Red" : "Black") << ")" << std::endl;

        inOrderHelper(node->right); // Traverse right subtree
    }
}

/*
* Public inOrder: Initiates an in-order traversal
*/
void RedBlackTree::inOrder() const {
    inOrderHelper(root);
}

/*
* leftRotate: Performs a left rotation on node x.
*/
void RedBlackTree::leftRotate(std::shared_ptr<RBTreeNode> x) {
    if (!x || !x->right) return;
    auto y = x->right;           // Set y as x's right child
    x->right = y->left;          // Move y's left subtree to become x's right subtree
    if (y->left) {
        // Update parent pointer of y's left child to x
        y->left->parent = x;
    }

    // Link x's parent to y
    if (auto xParent = x->parent.lock()) {
        if (x.get() == xParent->left.get()) {
            xParent->left = y;
        }
        else {
            xParent->right = y;
        }
        y->parent = xParent;  // Assign parent's shared pointer to y's weak parent pointer
    }
    else {
        // x was the root
        root = y;
        y->parent.reset();
    }

    // Put x as left child of y
    y->left = x;
    x->parent = y;  // Assign y (shared pointer) to x's weak parent pointer
}

/*
* rightRotate: Performs a right rotation on node x.
*/
void RedBlackTree::rightRotate(std::shared_ptr<RBTreeNode> x) {
    if (!x || !x->left) return;
    auto y = x->left;            // Set y as x's left child
    x->left = y->right;          // Move y's right subtree to become x's left subtree
    if (y->right) {
        // Update parent pointer of y's right child to x
        y->right->parent = x;
    }

    // Link x's parent to y
    if (auto xParent = x->parent.lock()) {
        if (x.get() == xParent->right.get()) {
            xParent->right = y;
        }
        else {
            xParent->left = y;
        }
        y->parent = xParent;
    }
    else {
        // x was the root
        root = y;
        y->parent.reset();
    }

    // Put x as right child of y
    y->right = x;
    x->parent = y;
}

/*
* insertFixup: Restores the Red–Black Tree properties after a new node is inserted. This method
*              handles three cases based on the color of the node's uncle and its relative position.
*              It uses rotations (leftRotate and rightRotate) and recoloring to ensure that:
*                 1. The root remains black.
*                 2. Red nodes do not have red children.
*                 3. Every path from a node to its descendant NIL nodes contains the same number of black nodes.
*/
void RedBlackTree::insertFixup(std::shared_ptr<RBTreeNode> z) {
    // While the parent exists and is red (violating properties)
    while (z->parent.lock() && z->parent.lock()->color == RED) {
        auto zParent = z->parent.lock();
        auto zGrandparent = zParent->parent.lock();
        if (!zGrandparent)
            break;  // Safety check
        // If parent is the left child of grandparent
        if (zParent == zGrandparent->left) {
            auto y = zGrandparent->right; // y is z's uncle
            if (y && y->color == RED) {
                // Case 1: Uncle is red
                zParent->color = BLACK;
                y->color = BLACK;
                zGrandparent->color = RED;
                z = zGrandparent; // Move up the tree
            }
            else {
                if (z.get() == zParent->right.get()) {
                    // Case 2: z is a right child -> convert to Case 3
                    z = zParent;
                    leftRotate(z);
                    zParent = z->parent.lock();
                    zGrandparent = zParent ? zParent->parent.lock() : nullptr;
                }
                // Case 3: z is a left child
                if (zParent)
                    zParent->color = BLACK;
                if (zGrandparent) {
                    zGrandparent->color = RED;
                    rightRotate(zGrandparent);
                }
            }
        }
        else {  // zParent is right child of zGrandparent
            auto y = zGrandparent->left; // y is z's uncle
            if (y && y->color == RED) {
                // Case 1: Uncle is red
                zParent->color = BLACK;
                y->color = BLACK;
                zGrandparent->color = RED;
                z = zGrandparent; // Move up the tree
            }
            else {
                if (z.get() == zParent->left.get()) {
                    // Case 2: z is a left child -> convert to Case 3
                    z = zParent;
                    rightRotate(z);
                    zParent = z->parent.lock();
                    zGrandparent = zParent ? zParent->parent.lock() : nullptr;
                }
                // Case 3: z is a right child
                if (zParent)
                    zParent->color = BLACK;
                if (zGrandparent) {
                    zGrandparent->color = RED;
                    leftRotate(zGrandparent);
                }
            }
        }
    }
    if (root)
        root->color = BLACK;  // Ensure the root is black
}

/*
*  insert: Inserts a new course into the Red-Black Tree.
*/
void RedBlackTree::insert(const Course& course) {
    auto newNode = std::make_shared<RBTreeNode>(course);
    // Initialize the new node; its color is set to RED by default.
    newNode->color = RED;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->parent.reset();

    std::shared_ptr<RBTreeNode> y = nullptr;
    auto x = root;
    // Traverse the tree to find the insertion point.
    while (x) {
        y = x;
        if (newNode->course.courseNumber < x->course.courseNumber)
            x = x->left;
        else
            x = x->right;
    }
    // Set the parent pointer.
    if (!y) {
        root = newNode;  // Tree was empty, new node becomes root.
    }
    else if (newNode->course.courseNumber < y->course.courseNumber) {
        y->left = newNode;
        newNode->parent = y;  // Assign shared_ptr y to newNode's weak parent.
    }
    else {
        y->right = newNode;
        newNode->parent = y;
    }
    // Restore tree balance and properties.
    insertFixup(newNode);
}

/*
*  searchHelper: Recursively searches for a course node with a specified courese number.
*/
std::shared_ptr<RBTreeNode> RedBlackTree::searchHelper(const std::shared_ptr<RBTreeNode>& node, const std::string& courseNumber) const {
    if (!node || node->course.courseNumber == courseNumber)
        return node;
    if (courseNumber < node->course.courseNumber)
        return searchHelper(node->left, courseNumber);
    else
        return searchHelper(node->right, courseNumber);
}

/*
* search: Public search method that searches for a course by course number and returns it if found.
*/
std::optional<Course> RedBlackTree::search(const std::string& courseNumber) const {
    auto node = searchHelper(root, courseNumber);
    if (node)
        return node->course;
    return std::nullopt;
}

/*
* loadDataStructure: Loads course data from a CSV file. For each line, it tokenizes the CSV data,
// creates a Course, and inserts it into the Red–Black Tree.
*/
void RedBlackTree::loadDataStructure(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << fileName << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;  // Skip empty lines
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        // Tokenize the line based on commas
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() >= 2) {
            Course newCourse(tokens[0], tokens[1]);
            // Add any additional tokens as prerequisites
            for (size_t i = 2; i < tokens.size(); ++i) {
                newCourse.addPrerequisite(tokens[i]);
            }
            insert(newCourse);
        }
        else {
            std::cerr << "Error: Invalid format for course data: " << line << std::endl;
        }
    }
    file.close();
}