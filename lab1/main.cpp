#include <iostream>
using namespace std;


// // // Node
class Person {
    friend class List;

    string firstName;
    string lastName;
    int age;
    Person* next;

public:
    Person(string f, string l, int a) {
        this->firstName = f;
        this->lastName = l;
        this->age = a;
        this->next = nullptr;
    }
};

// // // List

class List {
    Person* head = nullptr;
    Person* tail = nullptr;

public:
    List() { head = nullptr; }
    List(Person* newNode) { head = newNode; }

    void insertNode(Person* newNode);
    void printList();
};

void List::insertNode(Person* newNode) {
    if(!head) {
        head = newNode;
        tail = head;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void List::printList() {

    if (!head) {
        cout << "Empty list!\n";
    }

    Person* temp = head;
    while (temp) {
        cout << temp->firstName << " " << temp->lastName << ", " << temp->age;
        temp = temp->next;
    }
}

// // // // // // // // // // // // // // // // // // //

int main() {

    Person test1 = Person("Jakub", "Wawrzyczek", 19);

    // tworzenie listy (narazie pusta)
    List list1;
    // widac ze jest pusta
    list1.printList();


    // dodawanie node'ow do listy
    list1.insertNode(&test1);

    // printowanie zeby zobaczyc ze faktycznie sie dodaly
    list1.printList();
}
