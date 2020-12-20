#include "DAAL.h"
#include <iostream>

using namespace std;

int comparator(int a, int b) {
    return b-a;
}

int main(){
    LinkedList<int> list;
    list.add(2);
    list.add(1);
    list.add(4);
    list.add(5);
    list.add(-5);
    list.printAll();
    cout << list.get(2) << " should be 4\n";
    cout << list.get(0) << " should be 2\n";
    cout << list.get(5) << " should be null or garbage\n";
    cout << list.includes(4) << " should be true\n";
    list.reverse().printAll();
    cout << "should be reversed list\n";
    cout << list.size() << " should be 5\n";
    list.sort().printAll();
    cout << "should be sorted list\n";
    cout << list.removeIndex(0) << " should be 2\n";
    cout << list.size() << " should be 4\n";
    list.printAll();
    cout << list.pop() << " should be -5\n";
    cout << list.size() << " should be 3\n";
    list.printAll();
    cout << list.shift() << " should be 1\n";
    cout << list.size() << " should be 2\n";
    list.printAll();
    return 0;
}