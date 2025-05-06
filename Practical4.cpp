#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    bool isLeftThreaded;
    bool isRightThreaded;

    Node(int val) {
        data = val;
        left = right = nullptr;
        isLeftThreaded = false;
        isRightThreaded = false;
    }
};

class ThreadedBinaryTree {
private:
    Node* root;

    void threadTree(Node* node, Node*& prev) {
        if (node == nullptr) return;

        if (node->left == nullptr) {
            node->left = prev;
            node->isLeftThreaded = true;
        }

        if (prev != nullptr && prev->right == nullptr) {
            prev->right = node;
            prev->isRightThreaded = true;
        }

        prev = node;

        if (!node->isLeftThreaded) {
            threadTree(node->left, prev);
        }

        if (!node->isRightThreaded) {
            threadTree(node->right, prev);
        }
    }

    void preorderTraversal(Node* node) {
        while (node != nullptr) {
            cout << node->data << " ";

            if (node->left && !node->isLeftThreaded) {
                node = node->left;
            } else {
                node = node->right;
                while (node && node->isLeftThreaded) {
                    cout << node->data << " ";
                    node = node->right;
                }
                if (node ==nullptr) {
                    break;
                }
            }
        }
    }

public:
    ThreadedBinaryTree() {
        root = nullptr;
    }

    void insert(int data) {
        Node* newNode = new Node(data);
        if (root == nullptr) {
            root = newNode;
        } else {
            Node* current = root;
            Node* parent = nullptr;

            while (current != nullptr) {
                parent = current;
                if (data < current->data) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }

            if (data < parent->data) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }
    }

    void threadTree() {
        Node* prev = nullptr;
        threadTree(root, prev);
    }

    void preorderTraversal() {
        cout << "Preorder Traversal (without stack) using threads: ";
        preorderTraversal(root);
        cout << endl;
    }
};

int main() {
    ThreadedBinaryTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    tree.threadTree();
    tree.preorderTraversal();

    return 0;
}


