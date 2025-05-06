#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

class AVLTreeDictionary {
private:
    struct TreeNode {
        std::string key;
        std::string value;
        TreeNode* left;
        TreeNode* right;
        int height;

        TreeNode(std::string k, std::string v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    TreeNode* root;

    int getHeight(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int getBalanceFactor(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    void updateHeight(TreeNode* node) {
        if (node != nullptr) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* t2 = x->right;

        x->right = y;
        y->left = t2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* t2 = y->left;

        y->left = x;
        x->right = t2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    TreeNode* balance(TreeNode* node) {
        if (node == nullptr) {
            return node;
        }

        updateHeight(node);

        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    TreeNode* insert(TreeNode* node, std::string key, std::string value) {
        if (node == nullptr) {
            return new TreeNode(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;
            return node;
        }

        return balance(node);
    }

    TreeNode* deleteNode(TreeNode* node, std::string key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }

        return balance(node);
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    std::string findNode(TreeNode* node, std::string key) {
        if (node == nullptr) {
            return "";
        }

        if (key < node->key) {
            return findNode(node->left, key);
        } else if (key > node->key) {
            return findNode(node->right, key);
        } else {
            return node->value;
        }
    }

    void inorderTraversal(TreeNode* node, std::vector<std::pair<std::string, std::string>>& result) {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result.push_back({node->key, node->value});
            inorderTraversal(node->right, result);
        }
    }

    void reverseInorderTraversal(TreeNode* node, std::vector<std::pair<std::string, std::string>>& result) {
        if (node != nullptr) {
            reverseInorderTraversal(node->right, result);
            result.push_back({node->key, node->value});
            reverseInorderTraversal(node->left, result);
        }
    }

public:
    AVLTreeDictionary() : root(nullptr) {}

    void insert(std::string key, std::string value) {
        root = insert(root, key, value);
    }

    void remove(std::string key) {
        root = deleteNode(root, key);
    }

    std::string find(std::string key) {
        return findNode(root, key);
    }

    void displayAscending() {
        std::vector<std::pair<std::string, std::string>> result;
        inorderTraversal(root, result);
        for (const auto& pair : result) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    void displayDescending() {
        std::vector<std::pair<std::string, std::string>> result;
        reverseInorderTraversal(root, result);
        for (const auto& pair : result) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

    int maxComparisons() {
        return getHeight(root);
    }
};

int main() {
    AVLTreeDictionary dictionary;
    dictionary.insert("apple", "A fruit");
    dictionary.insert("banana", "Another fruit");
    dictionary.insert("cherry", "A small red fruit");
    dictionary.insert("date", "A sweet fruit");

    std::cout << "Find 'banana': " << dictionary.find("banana") << std::endl;

    dictionary.insert("banana", "A yellow fruit");

    std::cout << "Ascending order:\n";
    dictionary.displayAscending();

    std::cout << "\nDescending order:\n";
    dictionary.displayDescending();

    dictionary.remove("cherry");

    std::cout << "\nAscending order after delete:\n";
    dictionary.displayAscending();

    std::cout << "\nMaximum comparisons: " << dictionary.maxComparisons() << std::endl;

    return 0;
}


