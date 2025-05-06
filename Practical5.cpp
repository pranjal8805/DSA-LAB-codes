#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Structure for a node in the binary search tree
struct Node {
    string keyword;
    string meaning;
    Node* left;
    Node* right;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
    }
};

// Class for Dictionary (BST implementation)
class Dictionary {
private:
    Node* root;

    // Helper function to insert a node into the BST
    Node* insert(Node* node, const string& keyword, const string& meaning) {
        if (node == nullptr) {
            return new Node(keyword, meaning);
        }
        if (keyword < node->keyword) {
            node->left = insert(node->left, keyword, meaning);
        } else if (keyword > node->keyword) {
            node->right = insert(node->right, keyword, meaning);
        }
        return node;
    }

    // Helper function to delete a node from the BST
    Node* deleteNode(Node* root, const string& keyword) {
        if (root == nullptr) return root;

        if (keyword < root->keyword) {
            root->left = deleteNode(root->left, keyword);
        } else if (keyword > root->keyword) {
            root->right = deleteNode(root->right, keyword);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->keyword = temp->keyword;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->keyword);
        }
        return root;
    }

    // Helper function to find the minimum node in a tree
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Helper function for updating a keyword's meaning
    Node* update(Node* node, const string& keyword, const string& newMeaning) {
        if (node == nullptr) return node;
        if (keyword == node->keyword) {
            node->meaning = newMeaning;
        } else if (keyword < node->keyword) {
            node->left = update(node->left, keyword, newMeaning);
        } else {
            node->right = update(node->right, keyword, newMeaning);
        }
        return node;
    }

    // Helper function to display the dictionary in ascending order (inorder traversal)
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->keyword << ": " << node->meaning << endl;
        inorder(node->right);
    }

    // Helper function to display the dictionary in descending order (reverse inorder traversal)
    void reverseInorder(Node* node) {
        if (node == nullptr) return;
        reverseInorder(node->right);
        cout << node->keyword << ": " << node->meaning << endl;
        reverseInorder(node->left);
    }

    // Helper function to calculate the maximum depth of the tree (for maximum comparisons in binary search)
    int maxDepth(Node* node) {
        if (node == nullptr) return 0;
        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

public:
    Dictionary() {
        root = nullptr;
    }

    // Function to insert a new keyword and its meaning
    void insert(const string& keyword, const string& meaning) {
        root = insert(root, keyword, meaning);
    }

    // Function to delete a keyword
    void deleteKeyword(const string& keyword) {
        root = deleteNode(root, keyword);
    }

    // Function to update the meaning of a keyword
    void update(const string& keyword, const string& newMeaning) {
        root = update(root, keyword, newMeaning);
    }

    // Function to display the dictionary in ascending order
    void displayAscending() {
        inorder(root);
    }

    // Function to display the dictionary in descending order
    void displayDescending() {
        reverseInorder(root);
    }

    // Function to find the maximum number of comparisons required to find a keyword
    int maxComparisons() {
        return maxDepth(root);
    }
};

// Main function
int main() {
    Dictionary dict;

    while (true) {
        int choice;
        cout << "\nDictionary Menu: \n";
        cout << "1. Add new keyword\n";
        cout << "2. Delete keyword\n";
        cout << "3. Update keyword meaning\n";
        cout << "4. Display dictionary (ascending order)\n";
        cout << "5. Display dictionary (descending order)\n";
        cout << "6. Find max comparisons needed\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string keyword, meaning;
            cout << "Enter keyword: ";
            getline(cin, keyword);
            cout << "Enter meaning: ";
            getline(cin, meaning);
            dict.insert(keyword, meaning);
        } else if (choice == 2) {
            string keyword;
            cout << "Enter keyword to delete: ";
            getline(cin, keyword);
            dict.deleteKeyword(keyword);
        } else if (choice == 3) {
            string keyword, newMeaning;
            cout << "Enter keyword to update: ";
            getline(cin, keyword);
            cout << "Enter new meaning: ";
            getline(cin, newMeaning);
            dict.update(keyword, newMeaning);
        } else if (choice == 4) {
            cout << "Dictionary in ascending order:\n";
            dict.displayAscending();
        } else if (choice == 5) {
            cout << "Dictionary in descending order:\n";
            dict.displayDescending();
        } else if (choice == 6) {
            cout << "Maximum comparisons required to find a keyword: " << dict.maxComparisons() << endl;
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

