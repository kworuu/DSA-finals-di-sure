#include <iostream>
#include "arraylist.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    List* arr = new ArrayList();
    char op;
    int num, pos;

    do {
        cout << "OP: ";
        cin >> op;

        switch (op) {
        case 'a':
            cout << "Enter num: ";
            cin >> num;
            arr->add(num);
            break;
        case '@':
            cout << "Enter pos and num: ";
            cin >> pos >> num;
            arr->addAt(pos, num);
            break;
        case 'r':
            cout << "Enter num: ";
            cin >> num;
            arr->remove(num);
            break;
        case 'R':
            cout << "Enter pos: ";
            cin >> pos;
            cout << "Removed: " << arr->removeAt(pos) << endl;
            break;
        case 'A':
            cout << "Enter num: ";
            cin >> num;
            cout << "Removed count: " << arr->removeAll(num) << endl;
            break;
        case 's':
            cout << "Sum: " << arr->sumOfAll() << endl;
            break;
        case 'p':
            arr->print();
            break;
        default:
            break;
        }
    } while (op != 'x');
    cout << "Exiting..." << endl;

    delete arr;
    return 0;
}
