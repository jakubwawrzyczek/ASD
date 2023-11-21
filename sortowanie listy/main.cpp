#include <iostream>
#include "Node.h"
#include "List.h"

using namespace std;

int main() {

    List list1;
    list1.addT(-3);
    list1.addT(0);
    list1.addT(-8);
    list1.addT(-5);
    list1.addT(3);
    list1.addT(-2);
    list1.addT(12);
    list1.addT(16);
    list1.addT(23);
    list1.addT(56);

    list1.bubbleSort();
}
