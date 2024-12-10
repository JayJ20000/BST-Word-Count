#include "bst.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Function to clean a word by removing punctuation and converting to lowercase
string convertWord(string& word) {
    string convert;
    for (size_t i = 0; i < word.length(); ++i) {
        char c = word[i];
        // Allow alphanumeric characters and apostrophes
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '\'') {
            // Convert uppercase letters to lowercase
            if (c >= 'A' && c <= 'Z') {
                c = c + ('a' - 'A');
            }
            convert += c;
        }
    }
    return convert;
}

// Function to read words from a file and count their occurrences
void readFile(BST& bst, string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'.\n";
        return;
    }

    string word;
    while (file >> word) {
        string converted = convertWord(word);
        if (!converted.empty()) {
            int currentCount = bst.find(converted);
            if (currentCount == -1) {
                bst.set(converted, 1); // Add the word with count 1 if not present
            } else {
                bst.set(converted, currentCount + 1); // Increment count if present
            }
        }
    }

    file.close();
    cout << "File '" << filename << "' read successfully.\n";
}

// Function to display a menu
void menu(BST& bst) {
    int choice;
    string key;
    int value;

    do {
        cout << "\nBST Menu:\n";
        cout << "1. Insert or Update a Key-Value Pair\n";
        cout << "2. Find a Key\n";
        cout << "3. Print Tree In-Order\n";
        cout << "4. Delete a Key\n";
        cout << "5. Find Minimum Key\n";
        cout << "6. Find Maximum Key\n";
        cout << "7. Save Tree to File\n";
        cout << "8. Load Words from File\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key (string): ";
                cin >> key;
                cout << "Enter value (integer): ";
                cin >> value;
                bst.set(key, value);
                cout << "Key-Value pair inserted.\n";
                break;

            case 2:
                cout << "Enter key to find: ";
                cin >> key;
                value = bst.find(key);
                if (value != -1) {
                    cout << "Found! Value for key '" << key << "' is " << value << ".\n";
                } else {
                    cout << "Key '" << key << "' not found in the tree.\n";
                }
                break;

            case 3:
                cout << "Tree contents (in-order):\n";
                bst.print();
                break;

            case 4:
                cout << "Enter key to delete: ";
                cin >> key;
                bst.deleteKey(key);
                cout << "Delete operation completed for key '" << key << "'.\n";
                break;

            case 5:
                cout << "Finding the minimum key in the tree...\n";
                bst.min();
                break;

            case 6:
                cout << "Finding the maximum key in the tree...\n";
                bst.max();
                break;

            case 7:
                cout << "Enter filename to save tree: ";
                cin >> key; // Using `key` variable to store the filename
                bst.save_file(key);
                cout << "Tree saved to file '" << key << "'.\n";
                break;

            case 8:
                cout << "Enter filename to load words from: ";
                cin >> key; // Using `key` variable to store the filename
                readFile(bst, key);
                break;

            case 9:
                cout << "Exiting program. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 9);
}

int main() {
    BST bst;
    string filename;

    cout << "Binary Search Tree Program!\n";

    // Prompt the user for the filename
    cout << "Enter filename to load words from: ";
    cin >> filename;
    readFile(bst, filename);

    // Start the menu loop
    menu(bst);

    return 0;
}