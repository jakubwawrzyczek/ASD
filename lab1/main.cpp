#include <iostream>
using namespace std;


// // // Node
class Node {
    friend class List;

    int val;
    Node* next;

public:
    Node(int v) {
        this->val = v;
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

    void AddT(int newV);
    void AddH(int newV);
    void Add(Node* &p, int newV);
    void AddAfter(int v, int newV);
    void printList();
};

void List::AddT(int newV) {
    Node* newNode = new Node(newV);
    if(!head) {
        head = newNode;
        tail = head;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void List::AddH(int newV) {
    Node* newNode = new Node(newV);

    newNode->next = this->head;
    this->head = newNode;
}

void List::Add(Node* &p, int newV) {
    Node* newNode = new Node(newV);

    newNode->next = p->next;
    p->next = newNode;
}

void List::AddAfter(int v, int newV) {
    Node* p = head;

    while(p && p->val != v) {
        p=p->next;
    }

    if (p) {
        Add(p, newV);
    }
}

void List::printList() {

    if (!head) {
        cout << "Empty list!";
    }

    Node* temp = head;
    while (temp) {
        cout << temp->val << " ";
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

    // dodawanie po danej cyfrze
    list1.AddAfter(1, 2);
    list1.printList();

}