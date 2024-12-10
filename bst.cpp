#include "bst.h"
#include <iostream>
#include <fstream>

using namespace std;

// Constructor for Node class, initializes the node with a key, value, and sets its left and right child pointers to nullptr
Node::Node(string key, int value) {
    this->key = key;
    this->data = value;
    this->left = nullptr;
    this->right = nullptr;
}

// Constructor for BST class, initializes the root
BST::BST(){
    root = nullptr;
}

// Destructor for BST class, all dynamically allocated nodes are deleted
BST::~BST() {
    destructorHelper(root);
}

// Helper function to delete all nodes in the tree in post-order traversal 
void BST::destructorHelper(Node* current) {
    if (!current) return;
    destructorHelper(current->left);  // Recursively delete left subtree 
    destructorHelper(current->right); // Recursively delete right subtree 
    delete current;  // Delete the current node 
}

// Function to insert or update a key/value pair in the BST 
void BST::set(string key, int value) {
    Node** current = &root; // Start at the root of the tree 

    while (*current) { // Traverse the tree to find the correct position 
        if (key < (*current)->key) {
            current = &((*current)->left); // Go to the left child 
        } else if (key > (*current)->key) {
            current = &((*current)->right); // Go to the right child 
        } else {
            (*current)->data = value; // Key already exists; update the value 
            return;
        }
    }
    *current = new Node(key, value); // Create a new node if the key is not found 
}

// Function to find the value associated with a given key in the BST 
int BST::find(string key) {
    Node* current = root; // Start at the root of the tree 
    while (current) { // Traverse the tree to find the key 
        if (key < current->key) {
            current = current->left; // Go to the left child 
        } else if (key > current->key) {
            current = current->right; // Go to the right child 
        } else {
            return current->data; // Key found; return value 
        }
    }
    return -1; // Key not found; return -1 
}

// Helper function to print the tree in in-order traversal
void BST::printHelper(Node* current) {
    if (!current) return;
    printHelper(current->left); // Visit the left subtree 
    cout << "(" << current->key << ", " << current->data << ") "; // Print current node 
    printHelper(current->right); // Visit the right subtree 
}

// Wrapper function to print the entire tree 
void BST::print() {
    printHelper(root); // Call the helper function starting from the root 
    cout << endl;
}

// Function to find the minimum key in the BST 
string BST::min() {
    if (!root) {
        cerr << "Error: BST is empty. No minimum key exists.\n";
        return "";
    }

    Node* current = root;
    while (current->left) { // Traverse to the leftmost node 
        current = current->left;
    }

    return current->key; // Return the key of the leftmost node 
}

// Function to find the maximum key in the BST 
string BST::max() {
    if (!root) {
        cerr << "Error: BST is empty. No maximum key exists.\n";
        return "";
    }

    Node* current = root;
    while (current->right) { // Traverse to the rightmost node 
        current = current->right;
    }

    return current->key; // Return the key of the rightmost node 
}

// Helper function to save the contents to a file in in-order traversal 
void BST::saveHelper(Node* current, ofstream &outFile) {
    if (!current) return;
    saveHelper(current->left, outFile); // Visit the left subtree 
    outFile << current->key << " " << current->data << endl; // Save current node 
    saveHelper(current->right, outFile); // Visit the right subtree 
}

// Function to save the contents to a file 
void BST::save_file(string filename) {
    ofstream outFile(filename); // Open the file
    if (!outFile) {
        cerr << "Error: Failed to open file '" << filename << "' for writing.\n";
        return;
    }
    saveHelper(root, outFile); // Save the tree using the helper function 
    outFile.close(); // Close the file 
}

// Helper function to delete a node with the given key 
Node* BST::deleteHelper(Node* current, string key) {
    if (!current) return nullptr; // Base case: key not found 

    if (key < current->key)
        current->left = deleteHelper(current->left, key); // Go to the left subtree 
    else if (key > current->key)
        current->right = deleteHelper(current->right, key); // Go to the right subtree 
    else {
        // Node to delete found 
        if (!current->left) { // If node has no left child 
            Node* temp = current->right;
            delete current;
            return temp;
        } else if (!current->right) { // If node has no right child 
            Node* temp = current->left;
            delete current;
            return temp;
        }

        // Node has two children 
        Node* temp = current->right;
        while (temp && temp->left) // Find the in-order successor 
            temp = temp->left;

        // Replace current node's key and value with successor's key and value 
        current->key = temp->key;
        current->data = temp->data;
        current->right = deleteHelper(current->right, temp->key); // Delete the successor 
    }
    return current;
}

// Wrapper function to delete a node with the given key 
void BST::deleteKey(string key) {
    root = deleteHelper(root, key);
}
