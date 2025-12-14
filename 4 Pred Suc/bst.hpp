#include "binarytree.h"

class BST {
private:
    BinaryTree* tree;

    void insertRec(node* curr, int val) {
        if (val < curr->elem) {
            if (curr->left)
                insertRec(curr->left, val);
            else
                tree->addLeft(curr, val);
        } else {
            if (curr->right)
                insertRec(curr->right, val);
            else
                tree->addRight(curr, val);
        }
    }

    bool searchRec(node* curr, int val) {
        if (!curr) return false;
        if (curr->elem == val) return true;
        if (val < curr->elem) return searchRec(curr->left, val);
        return searchRec(curr->right, val);
    }

public:
    BST() {
        tree = new MyBinaryTree();
    }

    void insert(int val) {
        if (!tree->getRoot())
            tree->addRoot(val);
        else
            insertRec(tree->getRoot(), val);
    }

    bool search(int val) {
        return searchRec(tree->getRoot(), val);
    }

    // ==============================
    // PREDECESSOR (DO THIS PART)
    // ==============================
    int predecessor(int num) {
        node* curr = tree->getRoot();
        int pred = -1;

        while
    }

    // ==============================
    // SUCCESSOR (DO THIS PART)
    // ==============================
    int successor(int num) {
        
    }

    void print() {
        tree->print();
    }
};
