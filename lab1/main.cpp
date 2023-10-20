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

    // wstawianie elementow
    void addT(int newV);
    void addH(int newV);
    void add(Node* &p, int newV);
    void addAfter(int v, int newV);
    void duplicateEveryValue();
    void zad3();
    void duplicateEntireList();

    // usuwanie elementow
    void removeNext(Node* &p);
    void removeEvery2ndElement();
    void removeEvenElements();

    // lab3
    void lab31(); // zamien min z max
    void lab32(int x); // zamien element x z nastepnym
    void lab33(); // zamien co drugi element
    void lab34(); // zamien pierwszy z ostatnim

    // dzielenie listy
    void split1(Node* &head, Node* &head1, Node* &head2);
    void split2(Node* &head, Node* &head1, Node* &head2);
    void split3(Node* &head, Node* &head1, Node* &head2);
    // pierwsza lista ma elementy a dwie pozostale sa puste
    // po wykonaniu pierwsza lista jest pusta a dwie pozostale maja po 1/2 elementow

    // laczenie listy
    void merge(Node* &head, Node* &head1, Node* &head2);
    // polaczyc dwie posortowane listy

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

void List::removeEvery2ndElement() {
    Node* p = head;

    while (p && p->next) {
        removeNext(p);
        p = p->next;
    }
}

void List::removeEvenElements() {
    Node* p = head;

    while (head->val % 2 == 0) {
        head = head->next;
        p = head;
    }

    while (p && p->next) {
        if (p->next->val % 2 == 0) {
            removeNext(p);
        }
        else {
            p = p->next;
        }
    }
}

void List::lab32(int x) {
    addH(0);    // H -> [1] -> [2] -> [3]   =>   H -> [0] -> [1] -> [2] -> [3]
    Node* p = head;


    // przechodzi po liscie i szuka wartosci x a jesli na nia natrafi to ustawia wskaznik na elemencie poprzednim
    while(p->next && p->next->val != x) {
        p = p->next;
    }

    if(p->next == nullptr) {
        cout << "Value " << x << " not found\n";
    }
    else {
        // H -> [0] -> [1] -> [2] -> [3]
        //       ^      ^
        //       p     temp
        //
        // [0] -> [2], [1] -> [3], [2] -> [1]

        Node* temp = p->next;
        p->next = temp->next;
        temp->next = p->next->next;
        p->next->next = temp;

        Node* t2 = head;
        head = head->next;
        delete t2;
    }
}

void List::lab33() {
    addH(0);
    Node* p = head;

    while(p) {

        Node* temp = p->next;
        p->next = temp->next;
        temp->next = p->next->next;
        p->next->next = temp;

        if (p->next->next->next && p->next->next->next->next) {
            p = p->next->next;
        }

        else {
            p = nullptr;
        }
    }

    Node* t2 = head;
    head = head->next;
    delete t2;

}

void List::printList() {

    if (!head) {
        cout << "Empty list!";
    }

    else {
        cout << "H ";

        Node* temp = head;
        while (temp) {
            cout << "-> [" << temp->val << "] ";
            temp = temp->next;
        }
        cout << "-> NULL"<< endl;
    }

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

    List list3;
    list3.addT(1);
    list3.addT(2);
    list3.addT(3);
    list3.addT(4);
    list3.addT(5);
    cout << "\n\n\n";

    // zamien miejscami
    list3.printList();
    list3.lab32(1);
    list3.printList();

    cout << "\n\n\n";
    list3.printList();
    list3.lab33();
    list3.printList();


}