#include "Node.h"
#include "List.h"

#include <iostream>
using namespace std;

int main() {

List list1;
List list2;

//lista do wlozenia
list1.addT(5);
list1.addT(3);
list1.addT(2);
list1.addT(4);
list1.addT(6);
list1.addT(7);

//lista do ktorej bedziemy wkladac
list2.addT(1);
list2.addT(2);
list2.addT(3);
list2.addT(4);
list2.addT(5);
list2.addT(6);

list2.lab4zad1(list1.head);

list2.printList();
}