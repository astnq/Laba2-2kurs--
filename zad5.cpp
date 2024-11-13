//var 1
#include "include/tree.h"

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    TreeNode* root;

    BST() : root(nullptr) {}

    void insert(int val) {
        root = insertRec(root, val);
    }

    void remove(int val) {
        root = removeRec(root, val);
    }

    void inorder() {
        inorderRec(root);
        cout << std::endl;
    }

private:
    TreeNode* insertRec(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }

        if (val < node->value) {
            node->left = insertRec(node->left, val);
        } else if (val > node->value) {
            node->right = insertRec(node->right, val);
        }

        return node;
    }

    TreeNode* removeRec(TreeNode* node, int val) {
        if (node == nullptr) {
            return node; // Узел не найден
        }

        if (val < node->value) {
            node->left = removeRec(node->left, val);
        } else if (val > node->value) {
            node->right = removeRec(node->right, val);
        } else {
            // Узел найден

            // Удаление случая 1: Узел - лист
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Удаление случая 2: Узел имеет одного ребенка
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Удаление случая 3: Узел имеет двух детей
            // Найдем минимальный узел в правом поддереве
            TreeNode* minNode = findMin(node->right);
            node->value = minNode->value; // Замена значением минимального узла
            node->right = removeRec(node->right, minNode->value); // Удаляем минимальный узел
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void inorderRec(TreeNode* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            cout << node->value << " ";
            inorderRec(node->right);
        }
    }
};

int main() {
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder traversal of the BST: ";
    tree.inorder();

    cout << "Removing 20n";
    tree.remove(20);
    cout << "Inorder traversal after removing 20: ";
    tree.inorder();

    cout << "Removing 30n";
    tree.remove(30);
    cout << "Inorder traversal after removing 30: ";
    tree.inorder();

    cout << "Removing 50n";
    tree.remove(50);
    cout << "Inorder traversal after removing 50: ";
    tree.inorder();

    return 0;
}