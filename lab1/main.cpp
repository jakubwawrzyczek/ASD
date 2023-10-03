#include <iostream>
using namespace std;


// // // Node
class Node {
    friend class List;

    int data;
    Node* next;

public:
    Node(int d) {
        this->data = d;
        this->next = nullptr;
    }
};

// // // List

class List {
    Node* head = nullptr;
    Node* tail = nullptr;

public:
    List() { head = nullptr; }
    List(Node* newNode) { head = newNode; }

    void insertNode(Node* newNode);
    void printList();
};

void List::insertNode(Node* newNode) {
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

    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

// // // // // // // // // // // // // // // // // // //

int main() {

    Node node1 = Node(1);
    Node node2 = Node(2);
    Node node3 = Node(3);
    Node node4 = Node(4);

    // tworzenie listy (narazie pusta)
    List list1;
    // widac ze jest pusta
    list1.printList();


    // dodawanie node'ow do listy
    list1.insertNode(&node1);
    list1.insertNode(&node2);
    list1.insertNode(&node3);
    list1.insertNode(&node4);
    // printowanie zeby zobaczyc ze faktycznie sie dodaly
    list1.printList();
}
