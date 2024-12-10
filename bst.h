# Author: Jalen Jones
# Date: 12/7/2024

#ifndef BST_H
#define BST_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Node class represents each node in the Binary Search Tree (BST)
class Node {
public:
    // Constructor
    Node(string key, int value);
    
    // The key associated with the node
    string key;
    
    // The data/value associated with the key
    int data;
    
    // Pointer to the left child
    Node *left;
    
    // Pointer to the right child
    Node *right;
};


class BST {
private:
    Node* root;  // Pointer to the root node of the tree

    // Helper function to delete all nodes in the tree
    void destructorHelper(Node* current);

    // Helper function to print the tree (in-order traversal)
    void printHelper(Node* current);

    // Helper function to delete a node with the given key
    Node* deleteHelper(Node* current, string key);

    // Helper function to save the contents to a file
    void saveHelper(Node* current, ofstream& outFile);

public:
    // Constructor: Initializes an empty tree
    BST();

    // Destructor: Cleans up memory by deleting all nodes in the tree
    ~BST();

    // Inserts a new key-value pair into the tree or updates the value if the key exists
    void set(string key, int value);

    // Finds the value associated with the given key
    int find(string key);

    // Prints the contents of the tree
    void print();

    // Finds and returns the minimum key in the tree
    string min();

    // Finds and returns the maximum key in the tree
    string max();

    // Saves the tree's contents to a file
    void save_file(string filename);

    // Deletes the node with the specified key from the tree
    void deleteKey(string key);
};

#endif // BST_H
