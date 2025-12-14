#include <cstdlib>

struct node {
	node **children;
	node *parent;
	int num_child;
	int elem;

    int depth() {
		if(parent == nullptr) {
		    return 0;
		}
		
		return 1 + parent->depth();
	}


    int height() {
		if(num_child == 0) {
		    return  0;
		}
		
		int maxHeight = 0;
		
		for(int i = 0; i < num_child; i++) {
		    int child_height = children[i]->height();
		    
		    if(child_height > maxHeight) {
		        maxHeight = child_height;
		    }
		}
		
		return maxHeight;
    }
};