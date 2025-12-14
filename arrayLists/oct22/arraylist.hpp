#include <iostream>
#include "list.hpp"
#include <cstdlib>
#include <cmath>
using namespace std;

class ArrayList : public List {
private:
    int* arr;
    int cap;
    int size;

    void resize() {
        cap = static_cast<int>(ceil(cap * 1.5));
        arr = (int*) realloc(arr, cap * sizeof(int));
    }

public:
    ArrayList() {
        cap = 5;
        size = 0;
        arr = (int*) calloc(cap, sizeof(int));
    }

    void add(int num) {
        if (size == cap) resize();
        arr[size++] = num;
    }

    void addAt(int pos, int num) {
        if (size == cap) resize();
        for (int i = size; i > pos; i--) {
            arr[i] = arr[i - 1];
        }
        arr[pos] = num;
        size++;
    }

    void remove(int num) {
        for (int i = 0; i < size; i++) {
            if (arr[i] == num) {
                for (int j = i; j < size - 1; j++) {
                    arr[j] = arr[j + 1];
                }
                size--;
                return;
            }
        }
    }

    int removeAt(int pos) {
        if (pos < 0 || pos >= size) {
            return -1;
        }
        int removed = arr[pos-1];
        for (int i = pos-1; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
        return removed;
    }

    int removeAll(int num) {
        int ctr = 0;
        for (int i = 0; i < size; i++) {
            if (arr[i] == num) {
                for (int j = i; j < size - 1; j++) {
                    arr[j] = arr[j + 1];
                }
                size--;
                ctr++;
                i--;
            }
        }
        return ctr;
    }

    int sumOfAll() {
        int sum = 0;
        for (int i = 0; i < size; i++) sum += arr[i];
        return sum;
    }

    void print() {
        for (int i = 0; i < size; i++) cout << arr[i] << " ";
        cout << endl;
    }
};
