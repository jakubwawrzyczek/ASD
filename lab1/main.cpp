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


public:
    Node* head = nullptr;
    Node* tail = nullptr;
    List() { head = nullptr; }
    List(Node* newNode) { head = newNode; }

    void AddT(int v);
    void AddH(int v);
    void Add(Node* &p, int v);
    void printList();
};

void List::AddT(int v) {
    Node* newNode = new Node(v);
    if(!head) {
        head = newNode;
        tail = head;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void List::AddH(int v) {
    Node* newNode = new Node(v);

    newNode->next = this->head;
    this->head = newNode;
}

void List::Add(Node* &p, int v) {
    Node* newNode = new Node(v);

    newNode->next = p->next;
    p->next = newNode;
}

void List::printList() {

    if (!head) {
        cout << "Empty list!";
    }

    Node* temp = head;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// // // // // // // // // // // // // // // // // // //

int main() {

    // tworzenie listy (narazie pusta)
    List list1;
    // widac ze jest pusta
    list1.printList();


    // dodawanie na koniec listy
    list1.AddT(1);
    list1.AddT(2);
    list1.AddT(3);
    list1.printList();

    // dodawanie na poczatek listy
    list1.AddH(4);
    list1.printList();

    // dodawanie po danym wskazniku (po headzie)
    list1.Add(list1.head, 5);
    list1.printList();

}