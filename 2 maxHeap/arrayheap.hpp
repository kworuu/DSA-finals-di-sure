#include <iostream>
#include <cstdlib>
#include <cmath>
#include "maxheap.hpp"
using namespace std;

class ArrayMaxHeap : public MaxHeap {
    int* array;
    int size;
    int capacity = 5;

	int left(int i) {
        // TODO return the index of the left child of index i
		return (2 * i) + 1;
	}

	int right(int i) {
        // TODO return the index of the right child of index i
		return (2 * i) + 2;
	}
	
	void swap(int child, int parent) {
	    int temp = array[child];
		array[child] = array[parent];
		array[parent] = temp;
	}

    public:
    ArrayMaxHeap() {
    	int size = 0;
		array = (int*) calloc(capacity, sizeof(int));
	}

	void insert(int num) {
	    if(size >= capacity) {
			capacity = capacity * 1.5;
			array = (int*) realloc(array, capacity * sizeof(int));
		}

		array[size++] = num;

		int curr = size-1;
		while(curr > 0) {
			int par = (curr - 1) / 2;

			if(array[curr] > array[par]) {
				swap(curr, par);
				curr = par;
			} else {
				break;
			}
		}
	}

	int removeMax() {
	    int rem = array[0];
		swap(0, size-1);
		size--;

		if(size < capacity * (3/4.0)) {
			capacity = capacity * 0.8;
			if(capacity < 5) capacity = 5;
			array = (int*) realloc(array, capacity * sizeof(int));
		}

		int curr = 0;
		while(curr < size) {
			int leftChild = left(curr);
			int rightChild = right(curr);
			int max;

			if(rightChild > size) {
				max = leftChild;
			} else {
				max = (array[leftChild] > array[rightChild]) ? leftChild : rightChild;
			}

			if(array[max] > array[curr]) {
				swap(max, curr);
				curr = max;
			} else {
				break;
			}
		}
	}

    // DO NOT modify the code below
	void print() {
		if (size == 0) {
			cout << "EMPTY" << endl;
			return;
		}
			cout << "Size: " << size << "/" << capacity << endl;
			cout << "TREE: " << endl;
			print_tree("", 0, false);

		cout << "ARRAY: ";
		for (int i = 0; i < size; i++) {
			cout << array[i] << " ";
		}
		cout << endl;
	}

	void print_tree(string prefix, int n, bool isLeft) {
		cout << prefix;
        cout << (isLeft ? "+--L: " : "+--R: " );
        cout << array[n] << endl;
		if (left(n) < size) {
			print_tree(prefix + "|   ", left(n), true);
		}
		if (right(n) < size) {
			print_tree(prefix + "|   ", right(n), false);
		}
	}
};