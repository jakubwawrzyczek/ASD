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

    void addT(int newV);
    void addH(int newV);
    void add(Node* &p, int newV);
    void addAfter(int v, int newV);

    void duplicateEveryValue();
    void zad3();
    void duplicateEntireList();

    void removeNext(Node* &p);
    void removeEvery2ndElement();
    void removeEvenElements();
    void removeH();

    void printList();
};

void List::addT(int newV) {
    Node* newNode = new Node(newV);
    if(!head) {
        head = newNode;
        tail = head;
        return;
    }

    tail->next = newNode;
    tail = newNode;
}

void List::addH(int newV) {
    Node* newNode = new Node(newV);

    newNode->next = this->head;
    this->head = newNode;
}

void List::add(Node* &p, int newV) {
    Node* newNode = new Node(newV);

    newNode->next = p->next;
    p->next = newNode;
}

void List::addAfter(int v, int newV) {
    Node* p = head;

    while(p && p->val != v) {
        p=p->next;
    }

    if (p) {
        add(p, newV);
    }
}

void List::duplicateEveryValue() {
    Node* p = head;
    while(p) {
        add(p, p->val);
        p = p->next->next;
    }
}

void List::zad3() {
    Node* p = head;

    while (p) {
        for (int i = 1 ; i < p->val ; i++) {
            add(p, p->val);
            p = p->next;
        }
        p = p->next;
    }
}

void List::duplicateEntireList() {
    Node* p = head;
    List tempList;

    while (p) {
        tempList.addT(p->val);
        p = p->next;
    }

    tail->next = tempList.head;
    tail = tempList.tail;
}

void List::removeNext(Node* &p) {
    // H -> [1] -> [2] -> [3]
    //       ^
    //       p
    // temp = p->next
    // p->next = p->next->next
    // delete temp

    Node* temp = p->next;
    p->next = p->next->next;
    delete temp;

}

//void List::removeEvery2ndElement() {
//    Node* p = head;
//
//    while (p && p->next) {
//        removeNext(p);
//        p = p->next;
//    }
//}

//void List::removeEvenElements() {
//    Node* p = head;
//
//    while (head->val % 2 == 0) {
//        head = head->next;
//        p = head;
//    }
//
//    while (p && p->next) {
//        if (p->next->val % 2 == 0) {
//            removeNext(p);
//        }
//        else {
//            p = p->next;
//        }
//    }
//}

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
    list1.addT(1);
    list1.addT(2);
    list1.addT(3);
    list1.printList();

    // dodawanie na poczatek listy
    list1.addH(4);
    list1.printList();

    // dodawanie po danym wskazniku (po headzie)
    list1.add(list1.head, 5);
    list1.printList();

    // dodawanie po danej cyfrze
    list1.addAfter(1, 2);
    list1.printList();

    // duplikowanie kazdej pojedynczej wartosci z listy
    list1.duplicateEveryValue();
    list1.printList();


    cout << "\n------------\n" << "New list\n";

    List list2;
    list2.addT(2);
    list2.addT(2);
    list2.addT(2);
    list2.addT(1);
    list2.addT(2);
    list2.addT(3);
    list2.addT(1);
    list2.addT(2);
    list2.printList();

    // tyle wystapien liczby jaka ma wartosc
    list2.zad3();
    list2.printList();

    // skopiowanie calej listy na koniec
    list2.duplicateEntireList();
    list2.printList();

    // usuwanie co drugiego elementu w liscie
    list2.removeEvery2ndElement();
    list2.printList();

    // usuwanie elementow parzystych z listy
    list2.removeEvenElements();
    list2.printList();

}