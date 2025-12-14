#include <stdexcept>
#include <string>
#include <iostream>
#include "gentree.hpp"
using namespace std;

class MyGenTree : public GenTree {
    private:
    node* root;
    int size;
    
    // FIXED: Return the created node
    node* createNode(int elem, node* par) {
        node* n = new node;
        n->elem = elem;
        n->num_child = 0;
        n->parent = par;
        n->children = new node*[10];
        for(int i = 0; i < 10; i++) {
            n->children[i] = NULL;
        }
        return n;
    }
    
    void dfs(node* n) {
        if(n == NULL) return;

        cout << n->elem << " ";
        for(int i = 0; i < n->num_child; i++) {
            dfs(n->children[i]);
        }
    }
    
    void pos(node* n) {
        if(n == NULL) return;

        for(int i = 0; i < n->num_child; i++) {
            dfs(n->children[i]);
        }
        cout << n->elem << " ";

    }
    
    void bfs(node* n) {
        node* Q[20];
        int pop = 0, push = 0;

        Q[push++] = n;

        while(pop < push) {
            node* curr = Q[pop++];
            cout << curr-> << " ";

            for(int i = 0; i < curr->num_child; i++) {
                Q[push++] = curr->children[i];
            }
        }
    }
    
    public:
    MyGenTree() {
        root = NULL;
        size = 0;
    }
    
    void depthFirst() {
        dfs(root);
        cout << endl;
    }
    
    void postOrder() {
        pos(root);
        cout << endl;
    }
    
    void breadthFirst() {
        bfs(root);
        cout << endl;
    }
    
    node* addRoot(int elem) {
        if(root) {
            throw logic_error("Tree already has root");
        }
        
        root = createNode(elem, NULL);  // FIXED: Assign returned value
        size++;  // FIXED: Increment size
        return root;
    }
    
    node* addChild(node* par, int elem) {
        if(par == NULL) {
            throw logic_error("Parent is NULL");
        }
        
        if(par->num_child >= 10) {
            throw logic_error("Parent has max children");
        }
        
        node* child = createNode(elem, par);  // FIXED: Assign returned value
        par->children[par->num_child++] = child;
        size++;  // FIXED: Increment size
        return child;
    }
    
    void remove(node* n) {
        if(n == NULL) {
            throw logic_error("Node is NULL");
        }
        
        if(n->num_child > 0) {
            throw logic_error("Has children");
        }
        
        // FIXED: Handle removing root
        if(n == root) {
            root = NULL;
            size--;
            delete[] n->children;
            delete n;
            return;
        }
        
        node* par = n->parent;
        
        // Remove from parent's children array
        for(int i = 0; i < par->num_child; i++) {
            if(par->children[i] == n) {
                for(int j = i; j < par->num_child-1; j++) {
                    par->children[j] = par->children[j + 1];
                }
                par->children[par->num_child-1] = NULL;  // ADDED: Clear last slot
                par->num_child--;  // FIXED: Decrement parent's child count
                break;
            }
        }
        
        size--;
        delete[] n->children;
        delete n;
    }
    
    int getSize() {
        return size;
    }
    
    node* getRoot() {
        return root;
    }
};