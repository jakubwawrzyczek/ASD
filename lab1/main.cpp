#include "Node.h"
#include "List.h"

#include <iostream>
using namespace std;

int main() {

    List list1;

    list1.addH(1);
    list1.addH(2);
    list1.addT(3);
    list1.addAfter(2, 4);

    list1.removeByValue(1);

    list1.printList();

}