#include <iostream>
#include "Node.h"
#include "List.h"

using namespace std;

int main() {

    List list1;
    list1.addH(56);
    list1.addH(23);
    list1.addH(16);
    list1.addH(12);
    list1.addH(3);
    list1.addH(-5);
    list1.addH(-2);
    list1.addH(-8);
    list1.addH(0);
    list1.addH(-3);

//    list1.bubbleSort();
    list1.combSort();

    list1.printList();
    cout << list1.getLength();
}
