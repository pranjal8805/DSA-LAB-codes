
#include <iostream>
#include <algorithm>
using namespace std;

// Structure for a node in the binary search tree
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// Class for Binary Search Tree (BST) implementation
class BinarySearchTree {
private:
    Node* root;

    // Helper function to insert a node into the BST
    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else {
            node->right = insert(node->right, val);
        }
        return node;
    }

    // Helper function to find the height (number of nodes in the longest path) of the tree
    int height(Node* node) {
        if (node == nullptr) return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    // Helper function to find the minimum data value in the tree
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper function to perform a search for a value
    bool search(Node* node, int val) {
        if (node == nullptr) return false;
        if (val == node->data) return true;
        if (val < node->data) return search(node->left, val);
        return search(node->right, val);
    }

    // Helper function to swap left and right subtrees at every node
    void swapSubtrees(Node* node) {
        if (node == nullptr) return;
        swap(node->left, node->right);  // Swap left and right pointers
        swapSubtrees(node->left);  // Recursively swap left and right subtrees
        swapSubtrees(node->right);  // Recursively swap left and right subtrees
    }

public:
    // Constructor
    BinarySearchTree() {
        root = nullptr;
    }

    // Function to insert a new node with the given value
    void insert(int val) {
        root = insert(root, val);
    }

    // Function to find the height of the tree (longest path from root)
    int findHeight() {
        return height(root);
    }

    // Function to find the minimum data value in the tree
    int findMinValue() {
        Node* minNode = findMin(root);
        if (minNode != nullptr) return minNode->data;
        return -1; // If tree is empty, return -1
    }

    // Function to swap the left and right subtrees at every node
    void swapTree() {
        swapSubtrees(root);
    }

    // Function to search for a specific value in the tree
    bool searchValue(int val) {
        return search(root, val);
    }

    // Function to display the tree (in-order traversal)
    void inorder(Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Wrapper function for inorder traversal (starting from root)
    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }
};

// Main function
int main() {
    BinarySearchTree bst;

    // Insert values in the given order
    cout << "Inserting values into the BST: 50, 30, 20, 40, 70, 60, 80\n";
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "In-order traversal of the tree: ";
    bst.inorderTraversal();

    // i. Insert a new node
    int newValue;
    cout << "Enter a value to insert: ";
    cin >> newValue;
    bst.insert(newValue);
    cout << "In-order traversal after insertion: ";
    bst.inorderTraversal();

    // ii. Find number of nodes in the longest path (height of the tree)
    cout << "The number of nodes in the longest path (height) from the root: " << bst.findHeight() << endl;

    // iii. Find the minimum data value found in the tree
    cout << "The minimum data value in the tree: " << bst.findMinValue() << endl;

  

    // v. Search a value
    int searchValueToFind;
    cout << "Enter a value to search: ";
    cin >> searchValueToFind;
    if (bst.searchValue(searchValueToFind)) {
        cout << "Value " << searchValueToFind << " is found in the tree." << endl;
    } else {
        cout << "Value " << searchValueToFind << " is not found in the tree." << endl;
    }
    
    // iv. Swap the left and right children at every node
    bst.swapTree();
    cout << "In-order traversal after swapping left and right subtrees: ";
    bst.inorderTraversal();

    return 0;
}

