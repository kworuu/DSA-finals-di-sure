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
    // PREDECESSOR 
    // ==============================
    int predecessor(int num) {
        node* curr = tree->getRoot();
        int pred = -1;

        while(curr) {
            if(num > curr->elem) {
                pred = curr->elem;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        return pred;
    }

    // ==============================
    // SUCCESSOR 
    // ==============================
    int successor(int num) {
        node* curr = tree->getRoot();
        int succ = -1;

        while(curr) {
            if(num < curr->elem) {
                succ = curr->elem;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        return succ;
    }

    void print() {
        tree->print();
    }
};
